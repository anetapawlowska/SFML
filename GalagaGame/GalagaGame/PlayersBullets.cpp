#include "stdafx.h"
#include "PlayersBullets.h"


PlayersBullets::PlayersBullets()
{
}


PlayersBullets::~PlayersBullets()
{
}

void PlayersBullets::update()
{
	for (auto& pos : m_bullets)
	{
		pos.y -= step;
	}
	auto toRemoveIt = std::remove_if(begin(m_bullets), end(m_bullets), [](Position p) {return p.y > 480; });
	m_bullets.erase(toRemoveIt, end(m_bullets));
}

void PlayersBullets::render(sf::RenderWindow* window)
{
	sf::RectangleShape bullet{ sf::Vector2f{ 4.0f, 16.0f } };
	bullet.setFillColor(sf::Color::White);
	for (auto pos : m_bullets)
	{
		bullet.setPosition(pos.x, pos.y);
		window->draw(bullet);
	}
}

void PlayersBullets::add(Position position)
{
	m_bullets.push_back(position);
}

std::vector<Position>& PlayersBullets::getBulletsPositions()
{
	return m_bullets;
}

void PlayersBullets::start()
{
	m_bullets.clear();
}

void PlayersBullets::remove(Position pos)
{
	auto it = std::find(begin(m_bullets), end(m_bullets), pos);
	if (it != end(m_bullets))
		m_bullets.erase(it);
}
