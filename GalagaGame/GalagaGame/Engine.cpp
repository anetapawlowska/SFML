#include "stdafx.h"
#include "Engine.h"
#include "Window.h"

Engine::Engine() : m_enemies{&m_enemiesBullets}
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
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
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
		m_player.update();
		m_enemies.update();
		m_enemiesBullets.update();
	}
}

void Engine::render()
{
	m_window->beginDraw();
	m_player.render(m_window->getRenderWindow());
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