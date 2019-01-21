#pragma once

#include "string.h"
#include <SFML/Graphics.hpp>

class Window
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();
	void update();
	bool isDone() const;
	bool isFullScreen() const;
	sf::Vector2u getWindowSize() const;
	void toggleFullScreen();
	void draw(sf::Drawable& drawable);
	sf::RenderWindow* getRenderWindow();

private:
	void setup(const std::string& title, const sf::Vector2u& size);
	void destroy();
	void create();

	sf::RenderWindow m_window;
	std::string m_title;
	sf::Vector2u m_size;
	bool m_isDone{ false };
	bool m_isFullScreen{ false };
};

