#pragma once
#include "Bullets.h"

class EnemiesBullets : public Bullets
{
public:
	EnemiesBullets(sf::Vector2f windowSize);

	float getStep() const override;
};

