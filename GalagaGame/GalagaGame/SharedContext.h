#pragma once
#include <SFML\Graphics.hpp>

struct SharedContext
{
	SharedContext(sf::Vector2u windowSize) : windowSize{ windowSize } {}
	
	sf::Vector2u windowSize;
	long long unsigned points;
};
