#include "stdafx.h"
#include "PlayersMovement.h"


PlayersMovement::PlayersMovement(float playersStep, float playersMaxStep) : 
	m_playersStep{ playersStep }, m_playersMaxStep { playersMaxStep }
{
}


PlayersMovement::~PlayersMovement()
{
}

void PlayersMovement::keyPressed(sf::Keyboard::Key key)
{
	if (key != sf::Keyboard::Key::Right && key != sf::Keyboard::Key::Left)
		return;

	m_isKeyPressed = true;
	m_playersDirection = key == sf::Keyboard::Key::Right ? PlayersDirection::right : PlayersDirection::left;
	m_keyPressedCounter = 0;
}

void PlayersMovement::keyReleased(sf::Keyboard::Key key)
{
	if ((key == sf::Keyboard::Key::Right && m_playersDirection == PlayersDirection::right) ||
		(key == sf::Keyboard::Key::Left && m_playersDirection == PlayersDirection::left))
		m_isKeyPressed = false;
}

void PlayersMovement::clear()
{
	m_keyPressedCounter = 0;
	m_isKeyPressed = false;
	m_playersDirection = PlayersDirection::none;
}

void PlayersMovement::update(float deltaTime)
{
	if (m_playersDirection == PlayersDirection::none)
		return;

	if (m_isKeyPressed && getStep() < m_playersMaxStep)
		++m_keyPressedCounter;
	else if (m_keyPressedCounter > 0)
		--m_keyPressedCounter;

	if (m_keyPressedCounter == 0)
		m_playersDirection = PlayersDirection::none;
}

bool PlayersMovement::shouldMove() const
{
	return m_playersDirection != PlayersDirection::none;
}

// ========================== dummy logic ===============================

float PlayersMovement::getStep() const
{
	const float multiplier = 0.5f;
	float step = m_playersStep;
	step += m_keyPressedCounter * multiplier;
	step = std::min(step, m_playersMaxStep);
	if (m_playersDirection == PlayersDirection::left)
		step *= -1;
	return step;
}
