#include "stdafx.h"
#include "Player.h"
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

void Player::moveLeft()
{
	const auto pos = m_player.getPosition();
	if (pos.x > 0)
		m_player.setPosition(pos.x - m_step, pos.y);
}

void Player::moveRight()
{
	const auto pos = m_player.getPosition();
	if (pos.x < m_windowSize.x - m_size.x)
		m_player.setPosition(pos.x + m_step, pos.y);
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