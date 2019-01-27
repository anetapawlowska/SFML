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
	void moveSprite(EventDetails* details);

private:
	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;
	Window m_window;
};
