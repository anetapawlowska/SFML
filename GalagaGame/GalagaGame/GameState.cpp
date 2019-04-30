#include "stdafx.h"
#include "GameState.h"
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Enemies.h"
#include "Bullets.h"
#include "Enemy.h"
#include "StateManager.h"
#include "SharedContext.h"

GameState::GameState(StateManager* stateManager) : m_stateManager{ stateManager }
{
	const auto windowSize = m_stateManager->getSharedContext()->windowSize;
	const float playersBulletStep = -10.0f;
	const float enemysBulletStep = 10.0f;
	const sf::Color playersColor = sf::Color::Red;
	const sf::Color enemysColor = sf::Color::Blue;
	const sf::Color playersBulletsColor = sf::Color::White;
	const sf::Color enemiesBulletsColor = sf::Color::White;
	const float playersStep = 8.0f;
	const float enemiesFirstStep = 4.0f;
	const float enemiesSway = 0.5f;
	const sf::Vector2f enemiesBulletsSize{ 4.0f, 4.0f };
	const sf::Vector2f playersBulletsSize{ 4.0f, 4.0f };
	const sf::Vector2f playersSize{ 16.0f, 16.0f };
	const sf::Vector2f enemiesSize{ 16.0f, 16.0f };

	m_playersBullets = std::make_unique<Bullets>(windowSize, playersBulletsSize, playersBulletStep, playersBulletsColor);
	m_player = std::make_unique<Player>(m_playersBullets.get(), windowSize, playersSize, playersStep, playersColor);
	m_enemiesBullets = std::make_unique<Bullets>(windowSize, enemiesBulletsSize, enemysBulletStep, enemiesBulletsColor);
	m_enemies = std::make_unique<Enemies>(m_enemiesBullets.get(), windowSize, enemiesSize, enemiesFirstStep, enemysColor);

	m_font.loadFromFile("arial.ttf");
	m_pointsText.setFont(m_font);
	m_pointsText.setCharacterSize(15);
	m_pointsText.setFillColor(sf::Color::White);

	m_livesText.setFont(m_font);
	m_livesText.setCharacterSize(15);
	m_livesText.setFillColor(sf::Color::White);
	m_livesText.setString("Lives: " + std::to_string(m_lives));
	sf::FloatRect textRect = m_livesText.getLocalBounds();
	m_livesText.setPosition(windowSize.x - textRect.width, 0.0f);
}

GameState::~GameState()
{
}

void GameState::handleInput(sf::RenderWindow* window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
			m_player->moveRight();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			m_player->moveLeft();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			m_player->shoot();
	}
}

void GameState::update(float deltaTime) 
{
	if (m_enemies->getEnemies().empty())
		start();
	checkCollisions();
	m_playersBullets->update(deltaTime);
	m_player->update(deltaTime);
	m_enemiesBullets->update(deltaTime);
	m_enemies->update(deltaTime);
	m_pointsText.setString(std::to_string(m_stateManager->getSharedContext()->points));
}

void GameState::render(sf::RenderWindow* window)
{
	m_playersBullets->render(window);
	m_player->render(window);
	m_enemies->render(window);
	m_enemiesBullets->render(window);
	window->draw(m_pointsText);
	window->draw(m_livesText);
}

void GameState::onEnter()
{
	m_stateManager->getSharedContext()->points = 0;
	m_lives = 3;
}

void GameState::onLeave()
{
	clear();
}

void GameState::checkCollisions()
{
	auto bullets = m_enemiesBullets->getBulletsPositions();
	sf::RectangleShape bullet{ sf::Vector2f{ 4.0f, 16.0f } };
	for (auto bulletPos : bullets)
	{
		bullet.setPosition(bulletPos.x, bulletPos.y);
		if (isCollision(m_player->getPlayerShape(), bullet))
			killed();
	}

	auto enemies = m_enemies->getEnemies();
	sf::RectangleShape enemy{ sf::Vector2f{ 16.0f, 16.0f } };
	for (auto enemyPos : enemies)
	{
		enemy.setPosition(enemyPos.getPosition());
		if (isCollision(m_player->getPlayerShape(), enemy))
			killed();
	}

	auto playerBullets = m_playersBullets->getBulletsPositions();
	for (auto enemyPos : enemies)
	{
		enemy.setPosition(enemyPos.getPosition());
		for (auto bulletPos : playerBullets)
		{
			bullet.setPosition(bulletPos.x, bulletPos.y);
			if (isCollision(bullet, enemy))
			{
				m_enemies->killed(enemyPos.getPosition());
				addPointsForKill(enemyPos.getAction(), enemyPos.getType());
				m_playersBullets->remove(bulletPos);
			}
		}
	}
}

bool GameState::isCollision(sf::RectangleShape first, sf::RectangleShape second) const
{
	return first.getGlobalBounds().intersects(second.getGlobalBounds());
}

void GameState::start()
{
	clear();
	m_livesText.setString("Lives: " + std::to_string(m_lives));
	m_player->start();
	m_enemies->add();
}

void GameState::clear()
{
	m_enemies->clear();
	m_playersBullets->clear();
	m_enemiesBullets->clear();
}

void GameState::addPointsForKill(Enemy::Action action, Enemy::EnemyType type)
{
	unsigned points = (type == Enemy::EnemyType::shooter) ? 100 : 50;
	points *= (action == Enemy::Action::attack) ? 2 : 1;
	m_stateManager->getSharedContext()->points += points;
}

void GameState::killed()
{
	--m_lives;
	if (m_lives == 0)
		m_stateManager->setNextState(StateManager::States::GameOver);
	else
		start();
}