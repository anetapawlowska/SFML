#include "stdafx.h"
#include "Player.h"

#include <algorithm>

#include "Bullets.h"

Player::Player(Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color color) :
m_bullets{bullets}, m_windowSize{windowSize}
{
	m_shape.setSize(size);
	m_shape.setFillColor(color);
	m_shape.setPosition(getStartPosition());
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{

}

void Player::render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(m_shape);
}

void Player::move(float step)
{
	const auto pos = m_shape.getPosition();
	float newPos = pos.x + step;
	newPos = std::max(newPos, 0.0f);
	newPos = std::min(newPos, m_windowSize.x - m_shape.getSize().x);
	m_shape.setPosition(newPos, pos.y);
}

void Player::shoot()
{
	const auto playerPosition = m_shape.getPosition();
	const auto bulletsSize = m_bullets->getSize();
	const float x = playerPosition.x + m_shape.getSize().x / 2 - bulletsSize.x / 2;
	const float y = playerPosition.y - bulletsSize.y;
	m_bullets->add({x ,y});
}

sf::RectangleShape& Player::getPlayerShape()
{
	return m_shape;
}

void Player::start()
{
	m_shape.setPosition(getStartPosition());
}

sf::Vector2f Player::getStartPosition() const
{
	const auto size = m_shape.getSize();
	return{ m_windowSize.x / 2 - size.x / 2,  m_windowSize.y - 2 * size.y };
}