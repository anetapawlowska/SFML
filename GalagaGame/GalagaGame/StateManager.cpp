#include "stdafx.h"
#include "StateManager.h"
#include "State.h"
#include "GameState.h"

StateManager::StateManager()
{
	m_state = std::make_unique<GameState>();
}


StateManager::~StateManager()
{
}

void StateManager::handleInput(sf::RenderWindow* window)
{
	m_state->handleInput(window);
}

void StateManager::update(float deltaTime)
{
	m_state->update(deltaTime);
}

void StateManager::render(sf::RenderWindow* window) 
{
	m_state->render(window);
}

void StateManager::switchState(std::unique_ptr<State> state)
{
	m_state->onLeave();
	m_state = std::move(state);
	m_state->onEnter();
}