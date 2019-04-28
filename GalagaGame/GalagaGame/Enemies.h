#pragma once
#include <SFML\Graphics.hpp>
#include "Helpers.h"
#include "EnemiesBullets.h"

class Enemies
{
public:
	Enemies(EnemiesBullets* enemiesBullets);
	~Enemies();

	void update();
	void render(sf::RenderWindow* window);
	void add();
	void shoot(Position position);
	void start();
	std::vector<Position>& getPositions();
	void killed(Position pos);

private:
	std::vector<Position> m_enemiesPositions;
	EnemiesBullets* m_bullets;
	float step{ 8.0 };
};

