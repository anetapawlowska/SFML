#pragma once
#include <SFML\Graphics.hpp>
#include "EnemiesBullets.h"
#include "Enemy.h"

class Enemies
{
public:
	Enemies(EnemiesBullets* enemiesBullets, sf::Vector2f windowSize);
	~Enemies();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);
	void add();
	void shoot(sf::Vector2f position);
	void start();
	std::vector<Enemy>& getEnemies();
	void killed(sf::Vector2f pos);
	void attack(Enemy& enemy);

private:
	std::vector<Enemy> m_enemies;
	EnemiesBullets* m_bullets;
	const float m_step{ 4.0 };
	const float m_smallStep{0.5};
	float m_timeElapsed;
	sf::Vector2f m_windowSize;
	sf::Vector2f m_size;
	const unsigned m_swayInOneDirection = 10;
	unsigned m_sways = 0;
};

