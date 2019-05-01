#pragma once
#include <SFML\Graphics.hpp>
#include "Enemy.h"

class Bullets;

class Enemies
{
public:
	explicit Enemies(Bullets* enemiesBullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color shooterColor, sf::Color nonShooterColor);
	~Enemies();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void shoot(sf::Vector2f position);
	void clear();
	std::vector<Enemy>& getEnemies();
	void killed(sf::Vector2f pos);
	void add(unsigned numOfRows, float step);

private:
	bool shouldGoAttack() const;
	bool shouldFire() const;

	sf::Color m_shooterColor;
	sf::Color m_nonShooterColor;
	std::vector<Enemy> m_enemies;
	Bullets* m_bullets;
	float m_step{};
	const sf::Vector2u m_windowSize;
	const sf::Vector2f m_enemySize;
};

