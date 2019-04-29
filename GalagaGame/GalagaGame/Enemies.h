#pragma once
#include <SFML\Graphics.hpp>
#include "Bullets.h"
#include "Enemy.h"

class Enemies
{
public:
	Enemies(Bullets* enemiesBullets, sf::Vector2f windowSize, sf::Vector2f size, float step, sf::Color color);
	~Enemies();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);
	void add();
	void shoot(sf::Vector2f position);
	void start();
	std::vector<Enemy>& getEnemies();
	void killed(sf::Vector2f pos);

private:
	sf::Color m_color;
	std::vector<Enemy> m_enemies;
	Bullets* m_bullets;
	const float m_step;
	const float m_smallStep{0.5};
	float m_timeElapsed;
	const sf::Vector2f m_windowSize;
	const sf::Vector2f m_size;
	const unsigned m_swayInOneDirection = 10;
	unsigned m_sways = 0;
};

