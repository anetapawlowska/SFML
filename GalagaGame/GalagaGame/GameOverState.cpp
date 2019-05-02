#include "stdafx.h"
#include "GameOverState.h"
#include "StateManager.h"
#include "SharedContext.h"
#include "Config.h"
#include "ButtonShape.h"

GameOverState::GameOverState(StateManager* stateManager) : m_stateManager{ stateManager }
{
	const auto config = m_stateManager->getSharedContext()->config;
	const auto windowSize = config->windowSize;
	const auto startButtonPos = config->playAgainButtonsPos;
	const auto endButtonPos = config->endGameButtonsPos;
	const auto textPos = config->gameOverPointsPos;
	const auto buttonSize = config->buttonsSize;
	const auto color = config->buttonsColor;

	m_startButton = std::make_unique<ButtonShape>(config->buttonsSize, config->buttonsColor, startButtonPos, "Play again");
	m_endButton = std::make_unique<ButtonShape>(config->buttonsSize, config->buttonsColor, endButtonPos, "End game");

	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	setText();
	m_text.setCharacterSize(18);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(textPos);
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
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (m_startButton->isClicked(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				m_stateManager->setNextState(StateManager::States::Game);
			if (m_endButton->isClicked(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
				window->close();
		}
	}
}

void GameOverState::update(float deltaTime) 
{}
	
void GameOverState::render(sf::RenderWindow* window) 
{
	window->draw(m_text);
	m_startButton->render(window);
	m_endButton->render(window);
}

void GameOverState::onEnter()
{
	setText();
}

void GameOverState::onLeave() 
{}

void GameOverState::setText()
{
	auto* shared = m_stateManager->getSharedContext();
	++shared->m_level;
	m_text.setString("Points: " + std::to_string(shared->points) + "\nLevels: " + std::to_string(shared->m_level));
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

