#include "World.h"


World::World(sf::Vector2u windSize)
{
	m_blockSize = 16;
	m_windowSize = windSize;
	respawnApple();
	m_appleShape.setFillColor(sf::Color::Red);
	m_appleShape.setRadius(m_blockSize / 2);

	for (int i = 0; i < 4; ++i)
	{
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		
		if (!((i + 1) % 2))
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		else
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		
		if (i < 2)
			m_bounds[i].setPosition(0, 0);
		else
		{
			m_bounds[i].setOrigin(m_bounds[i].getSize());
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}


World::~World()
{
}

void World::respawnApple()
{
	int maxX = (m_windowSize.x / m_blockSize) - 2;
	int maxY = (m_windowSize.y / m_blockSize) - 2;
	m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	m_appleShape.setPosition(m_item.x * m_blockSize, m_item.y * m_blockSize);
}

void World::update(Snake& player)
{
	if (player.getPosition() == m_item)
	{
		player.extend();
		player.increaseScore();
		respawnApple();
	}

	int gridSizeX = m_windowSize.x / m_blockSize;
	int gridSizeY = m_windowSize.y / m_blockSize;

	if (player.getPosition().x <= 0 || player.getPosition().y <= 0
		|| player.getPosition().x >= gridSizeX - 1 || player.getPosition().y >= gridSizeY - 1)
		player.lose();
}

void World::render(sf::RenderWindow& window)
{
	for (int i = 0; i < 4; ++i)
		window.draw(m_bounds[i]);
	window.draw(m_appleShape);
}

int World::getBlockSize() const
{
	return m_blockSize;
}