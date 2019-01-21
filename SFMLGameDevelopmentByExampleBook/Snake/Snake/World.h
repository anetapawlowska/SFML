#pragma once
#include <SFML\Graphics.hpp>
#include "Snake.h"

class World
{
public:
	World(sf::Vector2u windSize);
	~World();

	int getBlockSize() const;
	void respawnApple();

	void update(Snake& player);
	void render(sf::RenderWindow& window);

private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;
	int m_blockSize;

	sf::CircleShape m_appleShape;
	sf::RectangleShape m_bounds[4];
};

