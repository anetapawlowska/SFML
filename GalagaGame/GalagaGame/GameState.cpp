#include "stdafx.h"
#include "GameState.h"
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Enemies.h"
#include "Bullets.h"
#include "Enemy.h"
#include "StateManager.h"
#include "SharedContext.h"
#include "Config.h"

GameState::GameState(StateManager* stateManager) : m_stateManager{ stateManager }
{
	Config* config = m_stateManager->getSharedContext()->config;

	m_playersBullets = std::make_unique<Bullets>(config->windowSize, config->playersBulletsSize, config->playersBulletsColor);
	m_player = std::make_unique<Player>(m_playersBullets.get(), config->windowSize, config->playersSize, config->playersStep, config->playersColor);
	m_enemiesBullets = std::make_unique<Bullets>(config->windowSize, config->enemiesBulletsSize, config->enemiesBulletsColor);
	m_enemies = std::make_unique<Enemies>(m_enemiesBullets.get(), config->windowSize, config->enemiesSize, config->enemysColor);

	m_font.loadFromFile("arial.ttf");
	m_pointsText.setFont(m_font);
	m_pointsText.setCharacterSize(15);
	m_pointsText.setFillColor(sf::Color::White);

	m_livesText.setFont(m_font);
	m_livesText.setCharacterSize(15);
	m_livesText.setFillColor(sf::Color::White);
	m_livesText.setString("Lives: " + std::to_string(m_lives));
	sf::FloatRect textRect = m_livesText.getLocalBounds();
	m_livesText.setPosition(config->windowSize.x - textRect.width, 0.0f);
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
	m_level = 0;
	start();
}

void GameState::onLeave()
{
	clear();
}

void GameState::checkCollisions()
{
	auto bullets = m_enemiesBullets->getBulletsPositions();
	sf::RectangleShape bulletShape{ sf::Vector2f{ 4.0f, 16.0f } };
	for (auto bulletPos : bullets)
	{
		bulletShape.setPosition(bulletPos.x, bulletPos.y);
		if (isCollision(m_player->getPlayerShape(), bulletShape))
			killMe();
	}

	auto enemies = m_enemies->getEnemies();
	sf::RectangleShape enemysShape{ sf::Vector2f{ 16.0f, 16.0f } };
	for (auto enemyPos : enemies)
	{
		enemysShape.setPosition(enemyPos.getPosition());
		if (isCollision(m_player->getPlayerShape(), enemysShape))
			killMe();
	}

	auto playerBullets = m_playersBullets->getBulletsPositions();
	for (auto enemy : enemies)
	{
		enemysShape.setPosition(enemy.getPosition());
		for (auto bulletPos : playerBullets)
		{
			bulletShape.setPosition(bulletPos.x, bulletPos.y);
			if (isCollision(bulletShape, enemysShape))
			{
				killTheEnemy(enemy, bulletPos);
				if (m_enemies->getEnemies().empty())
				{
					++m_level;
					start();
				}
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
	Config* config = m_stateManager->getSharedContext()->config;
	
	clear();
	m_livesText.setString("Lives: " + std::to_string(m_lives));
	m_player->start();

	const float bulletsStep = config->bulletsStep + m_level * config->nextLevelAcceleration;
	m_enemiesBullets->setStep(bulletsStep);
	m_playersBullets->setStep(-1 * bulletsStep);

	const unsigned numOfEnemiesRows = static_cast<unsigned>(config->numOfEnemiesRowsInFirstLevel + m_level * config->numOfEnemiesRowsMultiplier);
	const float enemiesSteps = config->enemiesFirstLevelStep + m_level * config->nextLevelAcceleration;
	m_enemies->add(numOfEnemiesRows, enemiesSteps );
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

void GameState::killMe()
{
	--m_lives;
	if (m_lives == 0)
		m_stateManager->setNextState(StateManager::States::GameOver);
	else
		start();
}

void GameState::killTheEnemy(Enemy enemy, sf::Vector2f bulletPos)
{
	m_enemies->killed(enemy.getPosition());
	addPointsForKill(enemy.getAction(), enemy.getType());
	m_playersBullets->remove(bulletPos);
}