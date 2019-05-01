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
	const auto buttonPos = config->playAgainButtonsPos;
	const auto textPos = config->gameOverPointsPos;
	const auto buttonSize = config->buttonsSize;
	const auto color = config->buttonsColor;

	m_button = std::make_unique<ButtonShape>(config->buttonsSize, config->buttonsColor, buttonPos, "play again");

	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	setText();
	m_text.setCharacterSize(15);
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
			if (m_button->isClicked(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
			m_stateManager->setNextState(StateManager::States::Game);
	}
}

void GameOverState::update(float deltaTime) 
{}
	
void GameOverState::render(sf::RenderWindow* window) 
{
	window->draw(m_text);
	m_button->render(window);
}

void GameOverState::onEnter()
{
	setText();
}

void GameOverState::onLeave() 
{}

void GameOverState::setText()
{
	m_text.setString("You won " + std::to_string(m_stateManager->getSharedContext()->points));
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

