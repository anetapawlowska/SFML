#pragma once
#include <SFML\Graphics.hpp>
#include <memory>

class State;

class StateManager
{
public:
	StateManager();
	~StateManager();

	void handleInput(sf::RenderWindow* window);
	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void switchState(std::unique_ptr<State> state);

private:
	std::unique_ptr<State> m_state;
};

