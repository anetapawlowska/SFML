#pragma once
#include <SFML\Graphics.hpp>

class State
{
public:
	virtual void handleInput(sf::RenderWindow* window) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow* window) = 0;

	virtual void onEnter() = 0;
	virtual void onLeave() = 0;

	virtual ~State() = default;
};