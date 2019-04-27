#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Window;

class Engine
{
public:
	Engine();
	~Engine();

	void handleInput();
	void update();
	void render();

	Window* getWindow();

private:
	std::unique_ptr<Window> m_window;
};