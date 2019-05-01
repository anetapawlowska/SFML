#include "stdafx.h"
#include "StartState.h"
#include "StateManager.h"
#include "SharedContext.h"
#include "Config.h"
#include "ButtonShape.h"

StartState::StartState(StateManager* stateManager): m_stateManager{stateManager}
{
	const auto config = m_stateManager->getSharedContext()->config;
	const auto windowSize = config->windowSize;
	const sf::Vector2f position = { windowSize.x / 2.0f, windowSize.y / 2.0f };
	std::string text = "play";
	m_button = std::make_unique<ButtonShape>(config->buttonsSize, config->buttonsColor, position, text);
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
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			if (m_button->isClicked (static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) ))
				m_stateManager->setNextState(StateManager::States::Game);
	}
}

void StartState::update(float deltaTime) 
{}

void StartState::render(sf::RenderWindow* window)
{
	m_button->render(window);
}

void StartState::onEnter() 
{}

void StartState::onLeave() 
{}
