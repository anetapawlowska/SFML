#include "stdafx.h"
#include "Engine.h"
#include "Player.h"
#include "Enemies.h"
#include "Bullets.h"

Engine::Engine()
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
	const sf::Vector2f playersSize{16.0f, 16.0f};
	const sf::Vector2f enemiesSize{ 16.0f, 16.0f };

	m_window.create({ 400, 480, 32 }, "Galaga", sf::Style::Default);

	m_playersBullets = std::make_unique<Bullets>(windowSize, playersBulletsSize, playersBulletStep, playersBulletsColor);
	m_player = std::make_unique<Player>(m_playersBullets.get(), windowSize, playersSize, playersStep, playersColor);
	m_enemiesBullets = std::make_unique<Bullets>(windowSize, enemiesBulletsSize, enemysBulletStep, enemiesBulletsColor);
	m_enemies = std::make_unique<Enemies>(m_enemiesBullets.get(), windowSize, enemiesSize, enemiesFirstStep, enemysColor);
}


Engine::~Engine()
{
}

void Engine::handleInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
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

void Engine::update()
{
	float timestep = 0.05f;
	if (m_elapsed.asSeconds() >= timestep)
	{
		m_elapsed -= sf::seconds(timestep);
		if (m_enemies->getEnemies().empty())
			start();
		checkCollisions();
		m_playersBullets->update(timestep);
		m_player->update(timestep);
		m_enemiesBullets->update(timestep);
		m_enemies->update(timestep);
	}
}

void Engine::render()
{
	m_window.clear(sf::Color::Black);
	m_playersBullets->render(getWindow());
	m_player->render(getWindow());
	m_enemies->render(getWindow());
	m_enemiesBullets->render(getWindow());
	m_window.display();
}

sf::RenderWindow* Engine::getWindow()
{
	return 
		&m_window;
}

sf::Time Engine::getElapsed() const
{
	return m_elapsed;
}

void Engine::restartClock()
{
	m_elapsed += m_clock.restart();
}

void Engine::checkCollisions()
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

bool Engine::isCollision(sf::RectangleShape first, sf::RectangleShape second) const
{
	return first.getGlobalBounds().intersects(second.getGlobalBounds());
}

void Engine::start()
{
	m_player->start();
	m_playersBullets->start();
	m_enemiesBullets->start();
	m_enemies->start();
}