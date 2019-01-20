#include "Game.h"


Game::Game() : m_window{ "Bouncing mushroom", sf::Vector2u{ 800, 600 } }
{
	m_mushroomTexture.loadFromFile("mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	m_increment = sf::Vector2i{ 400, 400 };
}


Game::~Game()
{
}

void Game::handleInput()
{

}

void Game::update()
{
	m_window.update();
	moveMushroom();
}

void Game::render()
{
	m_window.beginDraw();
	m_window.draw(m_mushroom);
	m_window.endDraw();
}

Window* Game::getWindow()
{
	return &m_window;
}

void Game::moveMushroom()
{
	sf::Vector2u windSize = m_window.getWindowSize();
	sf::Vector2u textSize = m_mushroomTexture.getSize();
	if ((m_mushroom.getPosition().x >
		windSize.x - textSize.x&&m_increment.x> 0) ||
		(m_mushroom.getPosition().x < 0 && m_increment.x< 0)){
		m_increment.x = -m_increment.x;
	}
	if ((m_mushroom.getPosition().y >
		windSize.y - textSize.y&&m_increment.y> 0) ||
		(m_mushroom.getPosition().y < 0 && m_increment.y< 0)){
		m_increment.y = -m_increment.y;
	}
	float elapsed = m_elapsed.asSeconds();
	m_mushroom.setPosition(
		m_mushroom.getPosition().x + m_increment.x * elapsed,
		m_mushroom.getPosition().y + m_increment.y * elapsed);
}

sf::Time Game::getElapsed() const
{
	return m_elapsed;
}

void Game::restartClock()
{
	m_elapsed = m_clock.restart();
}