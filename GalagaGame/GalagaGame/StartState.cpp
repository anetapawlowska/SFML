#include "stdafx.h"
#include "StartState.h"
#include "StateManager.h"
#include "SharedContext.h"
#include "Config.h"

StartState::StartState(StateManager* stateManager): m_stateManager{stateManager}
{
	const auto windowSize = m_stateManager->getSharedContext()->config->windowSize;
	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setString("Press Enter to start...");
	m_text.setCharacterSize(15);
	m_text.setFillColor(sf::Color::White);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
}

StartState::~StartState()
{
}

void StartState::handleInput(sf::RenderWindow* window)
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

void StartState::update(float deltaTime) 
{}

void StartState::render(sf::RenderWindow* window)
{
	window->draw(m_text);
}

void StartState::onEnter() 
{}

void StartState::onLeave() 
{}
