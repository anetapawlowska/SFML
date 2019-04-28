#pragma once
#include <SFML\Graphics.hpp>
#include "EnemiesBullets.h"

class Enemies
{
public:
	Enemies(EnemiesBullets* enemiesBullets);
	~Enemies();

	void update();
	void render(sf::RenderWindow* window);
	void add();
	void shoot(sf::Vector2f position);
	void start();
	std::vector<sf::Vector2f>& getPositions();
	void killed(sf::Vector2f pos);

private:
	std::vector<sf::Vector2f> m_enemiesPositions;
	EnemiesBullets* m_bullets;
	float step{ 8.0 };
};

