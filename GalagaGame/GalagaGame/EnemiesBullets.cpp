#include "stdafx.h"
#include "EnemiesBullets.h"


EnemiesBullets::EnemiesBullets(sf::Vector2f windowSize) : Bullets{windowSize}
{}

float EnemiesBullets::getStep() const
{
	return 10.f;
}