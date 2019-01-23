#pragma once

#include "Window.h"
#include "Snake.h"
#include "World.h"
#include "Textbox.h"

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
	World m_world;
	Snake m_snake;
	Window m_window;
	Textbox m_textbox;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};
