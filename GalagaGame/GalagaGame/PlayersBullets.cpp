#include "stdafx.h"
#include "PlayersBullets.h"

PlayersBullets::PlayersBullets(sf::Vector2f windowSize) : Bullets{ windowSize }
{}

float PlayersBullets::getStep() const
{
	return -10.f;
}
