#include "stdafx.h"
#include "Engine.h"
#include "Window.h"

Engine::Engine() :m_player{ &m_playersBullets }, m_enemies { &m_enemiesBullets }
{
	m_window = std::make_unique<Window>();
}


Engine::~Engine()
{
}

void Engine::handleInput()
{
	sf::Event event;
	while (m_window->getRenderWindow()->pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
			m_player.moveRight();
		else  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
			m_player.moveLeft();
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			m_player.shoot();
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
			m_enemies.add();
	}
}

void Engine::update()
{
	float timestep = 0.1f;
	if (m_elapsed.asSeconds() >= timestep)
	{
		m_elapsed -= sf::seconds(timestep);
		checkCollisions();
		m_window->update();
		m_playersBullets.update();
		m_player.update();
		m_enemiesBullets.update();
		m_enemies.update();
	}
}

void Engine::render()
{
	m_window->beginDraw();
	m_player.render(m_window->getRenderWindow());
	m_playersBullets.render(m_window->getRenderWindow());
	m_enemies.render(m_window->getRenderWindow());
	m_enemiesBullets.render(m_window->getRenderWindow());
	m_window->endDraw();
}

Window* Engine::getWindow()
{
	return m_window.get();
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

	auto enemies = m_enemies.getPositions();
	sf::RectangleShape enemy{ sf::Vector2f{ 16.0f, 16.0f } };
	for (auto enemyPos : enemies)
	{
		enemy.setPosition(enemyPos.x, enemyPos.y);
		if (isCollision(m_player.getPlayerShape(), enemy))
			start();
	}

	auto playerBullets = m_playersBullets.getBulletsPositions();
	for (auto enemyPos : enemies)
	{
		enemy.setPosition(enemyPos.x, enemyPos.y);
		for (auto bulletPos : playerBullets)
		{
			bullet.setPosition(bulletPos.x, bulletPos.y);
			if (isCollision(bullet, enemy))
			{
				m_enemies.killed(enemyPos);
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
	m_enemiesBullets.start();
	m_enemies.start();
}