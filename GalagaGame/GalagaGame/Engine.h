#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Config.h"
#include "SharedContext.h"

class StateManager;

class Engine
{
public:
	Engine();
	~Engine();

	void handleInput();
	void update();
	void render();
	sf::Time getElapsed() const;
	void restartClock();

	sf::RenderWindow* getWindow();

private:
	std::unique_ptr<StateManager> m_stateManager;
	std::unique_ptr<SharedContext> m_shared;
	Config m_config;

	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};