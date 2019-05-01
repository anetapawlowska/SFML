#include "stdafx.h"
#include "NonShooterEnemy.h"


NonShooterEnemy::NonShooterEnemy(Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color color, sf::Vector2f position)
	: Enemy{bullets, windowSize, size, color, position}
{
}


NonShooterEnemy::~NonShooterEnemy()
{
}

void NonShooterEnemy::shoot()
{

}