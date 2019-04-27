#include "stdafx.h"
#include "Player.h"


Player::Player() : m_player{sf::Vector2f{16.0f, 16.0f}}
{
	m_player.setFillColor(sf::Color::Red);
	m_player.setPosition(320, 448);
	m_player.setOrigin(8.0f, 8.0f);
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
	m_player.setPosition(m_player.getPosition().x - step, m_player.getPosition().y);
}

void Player::moveRight()
{
	m_player.setPosition(m_player.getPosition().x + step, m_player.getPosition().y);
}

sf::RectangleShape& Player::getPlayerShape()
{
	return m_player;
}

void Player::start()
{
	m_player.setPosition(320, 448);
}