#pragma once

#include "string.h"
#include <SFML/Graphics.hpp>
#include "EventManager.h"

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
	void draw(sf::Drawable& drawable);
	sf::RenderWindow* getRenderWindow();
	bool isFocused();
	EventManager* getEventManager();
	void toggleFullScreen(EventDetails* details = nullptr);
	void close(EventDetails* details = nullptr);

private:
	void setup(const std::string& title, const sf::Vector2u& size);
	void destroy();
	void create();

	EventManager m_eventManager;
	sf::RenderWindow m_window;
	std::string m_title;
	sf::Vector2u m_size;
	bool m_isDone{ false };
	bool m_isFullScreen{ false };
	bool m_isFocused;
};

