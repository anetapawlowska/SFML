#pragma once

#include "Window.h"

class Game
{
public:
	Game();
	~Game();

	void handleInput();
	void update();
	void render();
	Window* getWindow();
	sf::Time getElapsed() const;
	void restartClock();

private:
	void moveMushroom();
	Window m_window;
	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;
	sf::Vector2i m_increment;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};
