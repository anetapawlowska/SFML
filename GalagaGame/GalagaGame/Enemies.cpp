#include "stdafx.h"
#include "Enemies.h"


Enemies::Enemies(EnemiesBullets* enemiesBullets) : m_bullets{enemiesBullets}
{
}


Enemies::~Enemies()
{
}

void Enemies::update() 
{
	static int s = 0;
	++s;
	if (s == 16)
	{
		for (auto pos : m_enemiesPositions)
			shoot(pos);
		s = 0;
	}
	for (auto& pos : m_enemiesPositions)
	{
		pos.y += step;
	}
	auto toRemoveIt = std::remove_if(begin(m_enemiesPositions), end(m_enemiesPositions), [](sf::Vector2f p) {return p.y > 480; });
	m_enemiesPositions.erase(toRemoveIt, end(m_enemiesPositions));
	
}

void Enemies::render(sf::RenderWindow* window) 
{
	sf::RectangleShape enemy{ sf::Vector2f{ 16.0f, 16.0f } };
	enemy.setFillColor(sf::Color::Blue);
	for (auto pos : m_enemiesPositions)
	{
		enemy.setPosition(pos.x, pos.y);
		window->draw(enemy);
	}
}

void Enemies::add()
{
	m_enemiesPositions.push_back(sf::Vector2f{ 16.0f, 0.0f });
	m_enemiesPositions.push_back(sf::Vector2f{ 96.0f, 0.0f });
	m_enemiesPositions.push_back(sf::Vector2f{ 200.0f, 0.0f });
	m_enemiesPositions.push_back(sf::Vector2f{ 280.0f, 0.0f });
	m_enemiesPositions.push_back(sf::Vector2f{ 360.0f, 0.0f });
	m_enemiesPositions.push_back(sf::Vector2f{ 440.0f, 0.0f });
}

void Enemies::shoot(sf::Vector2f position)
{
	m_bullets->add(position);
}

void Enemies::start()
{
	m_enemiesPositions.clear();
}

std::vector<sf::Vector2f>& Enemies::getPositions()
{
	return m_enemiesPositions;
}

void Enemies::killed(sf::Vector2f pos)
{
	auto it = std::find(begin(m_enemiesPositions), end(m_enemiesPositions), pos);
	if (it != end(m_enemiesPositions))
		m_enemiesPositions.erase(it);
}