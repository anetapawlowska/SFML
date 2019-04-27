#pragma once
#include "Helpers.h"
#include <SFML\Graphics.hpp>
#include <vector>

class EnemiesBullets
{
public:
	EnemiesBullets();
	~EnemiesBullets();

	void update();
	void render(sf::RenderWindow* window);
	void add(Position position);
	std::vector<Position>& getBulletsPositions();
	void start();
private:
	std::vector<Position> m_bullets;
	float step{ 10.0f };
};

