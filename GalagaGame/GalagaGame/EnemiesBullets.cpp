#include "stdafx.h"
#include "EnemiesBullets.h"


EnemiesBullets::EnemiesBullets()
{
}


EnemiesBullets::~EnemiesBullets()
{
}

void EnemiesBullets::update() 
{
	for (auto& pos : m_bullets)
	{
		pos.y += step;
	}
	auto toRemoveIt = std::remove_if(begin(m_bullets), end(m_bullets), [](Position p) {return p.y > 480; });
	m_bullets.erase(toRemoveIt, end(m_bullets));
}

void EnemiesBullets::render(sf::RenderWindow* window) 
{
	sf::RectangleShape bullet{ sf::Vector2f{4.0f, 16.0f} };
	bullet.setFillColor(sf::Color::White);
	for (auto pos : m_bullets)
	{
		bullet.setPosition(pos.x, pos.y);
		window->draw(bullet);
	}
}

void EnemiesBullets::add(Position position)
{
	m_bullets.push_back(position);
}

std::vector<Position>& EnemiesBullets::getBulletsPositions()
{
	return m_bullets;
}

void EnemiesBullets::start()
{
	m_bullets.clear();
}
