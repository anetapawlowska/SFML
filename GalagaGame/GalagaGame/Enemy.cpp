#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(sf::Vector2u windowSize, sf::Vector2f size, sf::Color color, sf::Vector2f position, EnemyType type) : m_shape{ size },
m_windowSize{ windowSize }, m_position{ position }, m_startPosition{ position }, m_type{ type }
{
	m_shape.setFillColor(color);
}

Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime) 
{
	if (m_action == Action::attack && m_position.y >= m_windowSize.y)
	{
		m_position.y = -m_shape.getSize().y;
		m_action = Action::goBack;
	}
	if (m_action == Action::goBack && abs(m_position.y - m_startPosition.y) <= abs(m_step.y))
	{
		m_position = m_startPosition;
		m_action = Action::stayStill;
		m_step = { 0.0f, 0.0f };
	}

	m_position += m_step;
}

void Enemy::render(sf::RenderWindow* window) 
{
	m_shape.setPosition(m_position);
	window->draw(m_shape);
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

Enemy::EnemyType Enemy::getType() const
{
	return m_type;
}

void Enemy::attack(sf::Vector2f step)
{
	m_action = Action::attack;
	m_step = step;
}

sf::RectangleShape& Enemy::getShape()
{
	return m_shape;
}