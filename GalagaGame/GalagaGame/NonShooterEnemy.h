#pragma once
#include "Enemy.h"

class NonShooterEnemy : public Enemy
{
public:
	explicit NonShooterEnemy (Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color color, sf::Vector2f position);
	~NonShooterEnemy();

	void shoot() override;
};

