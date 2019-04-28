#include "stdafx.h"
#include "Engine.h"

Engine::Engine() :m_player{ &m_playersBullets, sf::Vector2f{ 400, 480 } }, m_enemies{ &m_enemiesBullets, sf::Vector2f{ 400, 480 } },
m_enemiesBullets{ sf::Vector2f{ 400, 480 } }, m_playersBullets{ sf::Vector2f{ 400, 480 } }
{
	m_window.create({ 400, 480, 32 }, "Galaga", sf::Style::Default);
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
			m_player.moveRight();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			m_player.moveLeft();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			m_player.shoot();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			m_enemies.add();
	}
}

void Engine::update()
{
	float timestep = 0.05f;
	if (m_elapsed.asSeconds() >= timestep)
	{
		m_elapsed -= sf::seconds(timestep);
		if (m_enemies.getEnemies().empty())
			start();
		checkCollisions();
		m_playersBullets.update(timestep);
		m_player.update(timestep);
		m_enemiesBullets.update(timestep);
		m_enemies.update(timestep);
	}
}

void Engine::render()
{
	m_window.clear(sf::Color::Black);
	m_playersBullets.render(getWindow());
	m_player.render(getWindow());
	m_enemies.render(getWindow());
	m_enemiesBullets.render(getWindow());
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
	auto bullets = m_enemiesBullets.getBulletsPositions();
	sf::RectangleShape bullet{ sf::Vector2f{ 4.0f, 16.0f } };
	for (auto bulletPos : bullets)
	{
		bullet.setPosition(bulletPos.x, bulletPos.y);
		if (isCollision(m_player.getPlayerShape(), bullet))
			start();
	}

	auto enemies = m_enemies.getEnemies();
	sf::RectangleShape enemy{ sf::Vector2f{ 16.0f, 16.0f } };
	for (auto enemyPos : enemies)
	{
		enemy.setPosition(enemyPos.getPosition());
		if (isCollision(m_player.getPlayerShape(), enemy))
			start();
	}

	auto playerBullets = m_playersBullets.getBulletsPositions();
	for (auto enemyPos : enemies)
	{
		enemy.setPosition(enemyPos.getPosition());
		for (auto bulletPos : playerBullets)
		{
			bullet.setPosition(bulletPos.x, bulletPos.y);
			if (isCollision(bullet, enemy))
			{
				m_enemies.killed(enemyPos.getPosition());
				m_playersBullets.remove(bulletPos);
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
	m_player.start();
	m_playersBullets.start();
	m_enemiesBullets.start();
	m_enemies.start();
}