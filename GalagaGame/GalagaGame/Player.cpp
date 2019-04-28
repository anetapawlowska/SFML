#include "stdafx.h"
#include "Player.h"
#include "PlayersBullets.h"

Player::Player(PlayersBullets* bullets, sf::Vector2f windowSize) :
m_bullets{bullets}, m_windowSize{windowSize}
{
	m_player.setSize(m_size);
	m_player.setFillColor(sf::Color::Red);
	m_startPosition.x = m_windowSize.x / 2 - m_size.x / 2;
	m_startPosition.y =  m_windowSize.y - 2 * m_size.y;
	m_player.setPosition(m_startPosition);
}

Player::~Player()
{
}

void Player::update()
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
		m_player.setPosition(pos.x - step, pos.y);
}

void Player::moveRight()
{
	const auto pos = m_player.getPosition();
	if (pos.x < m_windowSize.x - m_size.x)
		m_player.setPosition(pos.x + step, pos.y);
}

void Player::shoot()
{
	m_bullets->add(sf::Vector2f{ m_player.getPosition().x, m_player.getPosition().y });
}

sf::RectangleShape& Player::getPlayerShape()
{
	return m_player;
}

void Player::start()
{
	m_player.setPosition(m_startPosition);
}