#include "stdafx.h"
#include "Enemy.h"
#include "Bullets.h"

Enemy::Enemy(Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color color, 
	sf::Vector2f startPosition, sf::Vector2f position, sf::Vector2f step) :
	m_bullets{ bullets }, m_shape {size}, m_windowSize{ windowSize }, m_startPosition{ startPosition}, m_step{step}
{
	m_shape.setFillColor(color);
	m_shape.setPosition(position);
}

Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime) 
{
	auto position = m_shape.getPosition();
	if (m_action == Action::Attack && position.y >= m_windowSize.y)
	{
		position.y = -m_shape.getSize().y;
		m_action = Action::GoBack;
	}
	if (m_action == Action::GoBack && abs(position.y - m_startPosition.y) <= abs(m_step.y))
	{
		position = m_startPosition;
		m_action = Action::StayStill;
		m_step = { 0.0f, 0.0f };
	}

	position += m_step;
	m_shape.setPosition(position);
}

void Enemy::render(sf::RenderWindow* window) 
{
	window->draw(m_shape);
}

sf::Vector2f Enemy::getPosition() const 
{
	return m_shape.getPosition();
}

Enemy::Action Enemy::getAction() const
{
	return m_action;
}

void Enemy::attack(sf::Vector2f step)
{
	m_action = Action::Attack;
	m_step = step;
}

sf::RectangleShape& Enemy::getShape()
{
	return m_shape;
}

void Enemy::shoot()
{
	const auto position = m_shape.getPosition();
	const auto size = m_shape.getSize();
	const auto bulletsSize = m_bullets->getSize();
	const float x = position.x + size.x / 2 - bulletsSize.x / 2;
	const float y = position.y + size.y + m_step.y;
	m_bullets->add({ x,y });
}

void Enemy::goBack()
{
	m_shape.setPosition(m_startPosition);
	m_action = Action::StayStill;
	m_step = { 0.0f, 0.0f };
}