#pragma once
#include <vector>
#include "Bullets.h"

class PlayersBullets : public Bullets
{
public:
	PlayersBullets(sf::Vector2f windowSize);

	float getStep() const override;
};

