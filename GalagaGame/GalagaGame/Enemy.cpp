#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(sf::Vector2f windowSize, sf::Vector2f size, sf::Color color, sf::Vector2f position) : 
	m_windowSize{ windowSize }, m_size{ size }, m_color{ color }, m_position{ position }, m_startPosition{ position }
{
}


Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime) 
{
	if (m_action == Action::attack )
		if  (m_position.y >= m_windowSize.y)
	{
		m_position.y = -m_size.y;
		goBack();
	}
	if (m_action == Action::goBack)
		if( abs(m_position.x - m_startPosition.x) <= abs( m_step.x) && abs(m_position.y - m_startPosition.y) <= abs(m_step.y))
	{
		m_position = m_startPosition;
		m_action = Action::sway;
		m_step = { 0.0f, 0.0f };
	}

	m_position += m_step;
}

void Enemy::render(sf::RenderWindow* window) 
{
	sf::RectangleShape shape{ m_size };
	shape.setFillColor(m_color);
	shape.setPosition(m_position);
	window->draw(shape);
}

void Enemy::changeStep(sf::Vector2f step)
{
	m_step = step;
}

sf::Vector2f Enemy::getPosition() const 
{
	return m_position;
}

sf::Vector2f Enemy::getStep() const
{
	return m_step;
}

Enemy::Action Enemy::getAction() const
{
	return m_action;
}

void Enemy::attack(sf::Vector2f step)
{
	m_action = Action::attack;
	m_step = step;
}

void Enemy::goBack()
{
	const unsigned numOfSteps = std::ceil((m_startPosition.y - m_position.y) / 4.0f);
	const float stepX = (m_startPosition.x -  m_position.x) / numOfSteps;

	m_step = sf::Vector2f{ stepX , 4.0f };
	m_action = Action::goBack;
}