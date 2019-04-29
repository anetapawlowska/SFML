#include "stdafx.h"
#include "GameState.h"
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "Enemies.h"
#include "Bullets.h"

GameState::GameState()
{
	const sf::Vector2f windowSize{ 400.0f, 480.0f };
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
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			m_enemies->add();
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
}

void GameState::render(sf::RenderWindow* window)
{
	m_playersBullets->render(window);
	m_player->render(window);
	m_enemies->render(window);
	m_enemiesBullets->render(window);
}

void GameState::onEnter()
{}

void GameState::onLeave()
{}

void GameState::checkCollisions()
{
	auto bullets = m_enemiesBullets->getBulletsPositions();
	sf::RectangleShape bullet{ sf::Vector2f{ 4.0f, 16.0f } };
	for (auto bulletPos : bullets)
	{
		bullet.setPosition(bulletPos.x, bulletPos.y);
		if (isCollision(m_player->getPlayerShape(), bullet))
			start();
	}

	auto enemies = m_enemies->getEnemies();
	sf::RectangleShape enemy{ sf::Vector2f{ 16.0f, 16.0f } };
	for (auto enemyPos : enemies)
	{
		enemy.setPosition(enemyPos.getPosition());
		if (isCollision(m_player->getPlayerShape(), enemy))
			start();
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
	m_player->start();
	m_playersBullets->start();
	m_enemiesBullets->start();
	m_enemies->start();
}