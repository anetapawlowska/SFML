#include "stdafx.h"
#include "GameOverState.h"
#include "StateManager.h"
#include "SharedContext.h"

GameOverState::GameOverState(StateManager* stateManager) : m_stateManager{ stateManager }
{
	const auto windowSize = m_stateManager->getSharedContext()->windowSize;
	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	setText();
	m_text.setCharacterSize(15);
	m_text.setFillColor(sf::Color::White);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
}


GameOverState::~GameOverState()
{
}

void GameOverState::handleInput(sf::RenderWindow* window) 
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
			m_stateManager->setNextState(StateManager::States::Game);
	}
}

void GameOverState::update(float deltaTime) 
{}
	
void GameOverState::render(sf::RenderWindow* window) 
{
	window->draw(m_text);
}

void GameOverState::onEnter()
{
	setText();
}

void GameOverState::onLeave() 
{}

void GameOverState::setText()
{
	m_text.setString("Game Over\n\nYou won " + std::to_string(m_stateManager->getSharedContext()->points) + "\n\nPress Enter to start again...");
}

