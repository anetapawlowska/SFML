#include "Game.h"


Game::Game() : m_window{ "Snake", sf::Vector2u{ 800, 608 } }, 
m_snake(m_world.getBlockSize()), m_world(sf::Vector2u(800,608))
{
}


Game::~Game()
{
}

void Game::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.getPhysicalDirection() != Direction::Down)
		m_snake.setDirection(Direction::Up);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.getPhysicalDirection() != Direction::Up)
		m_snake.setDirection(Direction::Down);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.getPhysicalDirection() != Direction::Left)
		m_snake.setDirection(Direction::Right);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.getPhysicalDirection() != Direction::Right)
		m_snake.setDirection(Direction::Left);

}

void Game::update()
{
	m_window.update();
	float timestep = 1.0f / m_snake.getSpeed();

	if (m_elapsed.asSeconds() >= timestep)
	{
		m_snake.tick();
		m_world.update(m_snake);
		m_elapsed -= sf::seconds(timestep);
		if (m_snake.hasLost())
			m_snake.reset();
	}
}

void Game::render()
{
	m_window.beginDraw();
	m_world.render(*m_window.getRenderWindow());
	m_snake.render(*m_window.getRenderWindow());
	m_window.endDraw();
}

Window* Game::getWindow()
{
	return &m_window;
}

sf::Time Game::getElapsed() const
{
	return m_elapsed;
}

void Game::restartClock()
{
	m_elapsed += m_clock.restart();
}