#pragma once
#include <vector>
#include <SFML\Graphics.hpp>>
#include "Helpers.h"

class PlayersBullets
{
public:
	PlayersBullets();
	~PlayersBullets();

	void update();
	void render(sf::RenderWindow* window);
	void add(Position position);
	std::vector<Position>& getBulletsPositions();
	void start();
	void remove(Position pos);

private:
	std::vector<Position> m_bullets;
	float step{ 10.0f };
};

