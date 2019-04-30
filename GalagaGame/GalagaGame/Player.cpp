#include "stdafx.h"
#include "Player.h"
#include <algorithm>
#include "Bullets.h"

Player::Player(Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, float step, sf::Color color) :
m_bullets{bullets}, m_windowSize{windowSize}, m_size{size}, m_step{step}
{
	m_player.setSize(m_size);
	m_player.setFillColor(color);
	m_startPosition.x = m_windowSize.x / 2 - m_size.x / 2;
	m_startPosition.y =  m_windowSize.y - 2 * m_size.y;
	m_player.setPosition(m_startPosition);
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{

}

void Player::render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(m_player);
}

void Player::move(float step)
{
	const auto pos = m_player.getPosition();
	float newPos = pos.x + step;
	newPos = std::max(newPos, 0.0f);
	newPos = std::min(newPos, m_windowSize.x - m_size.x);
	m_player.setPosition(newPos, pos.y);
}

void Player::shoot()
{
	const auto playerPosition = m_player.getPosition();
	const auto bulletsSize = m_bullets->getSize();
	const float x = playerPosition.x + m_size.x / 2 - bulletsSize.x / 2;
	const float y = playerPosition.y - bulletsSize.y;
	m_bullets->add({x ,y});
}

sf::RectangleShape& Player::getPlayerShape()
{
	return m_player;
}

void Player::start()
{
	m_player.setPosition(m_startPosition);
}