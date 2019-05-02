#include "stdafx.h"
#include "NonShooterEnemy.h"


NonShooterEnemy::NonShooterEnemy(Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, 
	sf::Color color, sf::Vector2f startPosition, sf::Vector2f position, sf::Vector2f step)
	: Enemy{bullets, windowSize, size, color, startPosition, position, step}
{
}

NonShooterEnemy::~NonShooterEnemy()
{
}

void NonShooterEnemy::shoot()
{

}