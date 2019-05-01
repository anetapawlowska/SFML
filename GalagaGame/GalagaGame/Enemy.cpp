#include "stdafx.h"
#include "Enemy.h"
#include "Bullets.h"

Enemy::Enemy(Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color color, sf::Vector2f position) :
	m_bullets{ bullets }, m_shape {size}, m_windowSize{ windowSize }, m_startPosition{ position }
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
	if (m_action == Action::attack && position.y >= m_windowSize.y)
	{
		position.y = -m_shape.getSize().y;
		m_action = Action::goBack;
	}
	if (m_action == Action::goBack && abs(position.y - m_startPosition.y) <= abs(m_step.y))
	{
		position = m_startPosition;
		m_action = Action::stayStill;
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
	m_action = Action::attack;
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