#pragma once

#include "string.h"
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	~Window();

	void beginDraw();
	void endDraw();
	void update();
	bool isDone() const;
	sf::RenderWindow* getRenderWindow();

private:
	sf::RenderWindow m_window;
	bool m_isDone{ false };
};

