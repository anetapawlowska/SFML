#include "stdafx.h"
#include "Bullets.h"


Bullets::Bullets(sf::Vector2f windowSize) : m_windowSize{windowSize}
{
}


Bullets::~Bullets()
{
}

void Bullets::update(float deltaTime)
{
	if (m_bullets.empty())
		return;
	for (auto& pos : m_bullets)
	{
		pos.y += getStep();	
	}
	auto toRemoveIt = std::remove_if(begin(m_bullets), end(m_bullets), [&](sf::Vector2f p) {return p.y + m_size.y <= 0 || p.y >= m_windowSize.y; });
	m_bullets.erase(toRemoveIt, end(m_bullets));
}

void Bullets::render(sf::RenderWindow* window)
{
	sf::RectangleShape bullet{ m_size };
	bullet.setFillColor(sf::Color::White);
	for (auto pos : m_bullets)
	{
		bullet.setPosition(pos.x, pos.y);
		window->draw(bullet);
	}
}

void Bullets::add(sf::Vector2f position)
{
	m_bullets.push_back(position);
}

std::vector<sf::Vector2f>& Bullets::getBulletsPositions()
{
	return m_bullets;
}

void Bullets::start()
{
	m_bullets.clear();
}

void Bullets::remove(sf::Vector2f pos)
{
	auto it = std::find(begin(m_bullets), end(m_bullets), pos);
	if (it != end(m_bullets))
		m_bullets.erase(it);
}

sf::Vector2f Bullets::getSize() const
{
	return m_size;
}