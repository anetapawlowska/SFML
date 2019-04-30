#include "stdafx.h"
#include "StateManager.h"

#include "State.h"
#include "GameState.h"
#include "StartState.h"
#include "GameOverState.h"

StateManager::StateManager(SharedContext* shared) : m_shared{shared}
{
	m_states[States::Start] = std::make_shared<StartState>(this);
	m_states[States::Game] = std::make_shared<GameState>(this);
	m_states[States::GameOver] = std::make_shared<GameOverState>(this);
	m_currentState = m_states[States::Start];
}

StateManager::~StateManager()
{
}

void StateManager::handleInput(sf::RenderWindow* window)
{
	m_currentState->handleInput(window);
}

void StateManager::update(float deltaTime)
{
	m_currentState->update(deltaTime);
}

void StateManager::render(sf::RenderWindow* window) 
{
	m_currentState->render(window);
}

void StateManager::setNextState(States state)
{
	m_currentState->onLeave();
	m_currentState = m_states[state];
	m_currentState->onEnter();
}

SharedContext* StateManager::getSharedContext()
{
	return m_shared;
}