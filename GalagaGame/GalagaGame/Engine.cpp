#include "stdafx.h"
#include "Engine.h"
#include "StateManager.h"

Engine::Engine()
{
	m_window.create({ 400, 480, 32 }, "Galaga", sf::Style::Default);
	m_stateManager = std::make_unique<StateManager>(&m_shared);
}


Engine::~Engine()
{
}

void Engine::handleInput()
{
	m_stateManager->handleInput(getWindow());
}

void Engine::update()
{
	float timestep = 0.05f;
	if (m_elapsed.asSeconds() >= timestep)
	{
		m_elapsed -= sf::seconds(timestep);
		m_stateManager->update(timestep);
	}
}

void Engine::render()
{
	m_window.clear(sf::Color::Black);
	m_stateManager->render(getWindow());
	m_window.display();
}

sf::RenderWindow* Engine::getWindow()
{
	return &m_window;
}

sf::Time Engine::getElapsed() const
{
	return m_elapsed;
}

void Engine::restartClock()
{
	m_elapsed += m_clock.restart();
}