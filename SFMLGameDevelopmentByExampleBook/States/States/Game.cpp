#include "Game.h"
#include <iostream>
#include "EventManager.h"

Game::Game() : m_window{ "Events", sf::Vector2u{ 800, 608 } }, m_stateManager{&m_context}
{
	m_mushroomTexture.loadFromFile("mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	//m_window.getEventManager()->addCallback("Move", &Game::moveSprite, this);
	m_context.m_wind = &m_window;
	m_context.m_eventManager = m_window.getEventManager();
	m_stateManager.switchTo(StateType::Intro);
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
	m_stateManager.update(m_elapsed);
}

void Game::render()
{
	m_window.beginDraw();
	m_window.draw(m_mushroom);
	m_stateManager.draw();
	m_window.endDraw();
}

void Game::lateUpdate()
{
	m_stateManager.processRequests();
	restartClock();
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

sf::Time Game::getElapsed() const
{
	return m_elapsed;
}

void Game::restartClock()
{
	m_elapsed = m_clock.restart();
}