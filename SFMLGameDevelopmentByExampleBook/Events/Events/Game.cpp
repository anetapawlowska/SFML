#include "Game.h"
#include <iostream>
#include "EventManager.h"

Game::Game() : m_window{ "Events", sf::Vector2u{ 800, 608 } }
{
	m_mushroomTexture.loadFromFile("mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	m_window.getEventManager()->addCallback("Move", &Game::moveSprite, this);
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

void Game::moveSprite(EventDetails* details)
{
	sf::Vector2i mousepos = m_window.getEventManager()->getMousePos(m_window.getRenderWindow());
	m_mushroom.setPosition(mousepos.x, mousepos.y);
	std::cout << "moving sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
}