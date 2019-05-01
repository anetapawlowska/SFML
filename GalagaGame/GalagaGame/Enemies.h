#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include "Enemy.h"

class Bullets;

class Enemies
{
public:
	explicit Enemies(Bullets* enemiesBullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color shooterColor, sf::Color nonShooterColor);
	~Enemies();

	using EnemiesInfo = std::vector<std::unique_ptr<Enemy>>;

	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void clear();
	EnemiesInfo& getEnemies();
	void killed(Enemies::EnemiesInfo::iterator enemyIt);
	void add(unsigned numOfRows, float step);

private:
	bool shouldGoAttack() const;
	bool shouldFire() const;

	sf::Color m_shooterColor;
	sf::Color m_nonShooterColor;
	EnemiesInfo m_enemies;
	Bullets* m_bullets;
	float m_step{};
	const sf::Vector2u m_windowSize;
	const sf::Vector2f m_enemySize;
};

