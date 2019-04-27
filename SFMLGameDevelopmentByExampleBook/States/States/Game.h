#pragma once

#include "Window.h"
#include "StateManager.h"

class Game
{
public:
	Game();
	~Game();

	void handleInput();
	void update();
	void render();
	Window* getWindow();
	void moveSprite(EventDetails* details);
	void lateUpdate();
	sf::Time getElapsed() const;
	void restartClock();

private:
	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;
	Window m_window;
	StateManager m_stateManager;
	SharedContext m_context;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};
