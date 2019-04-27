#include "stdafx.h"
#include "Engine.h"
#include "Window.h"

Engine::Engine()
{
	m_window = std::make_unique<Window>();
}


Engine::~Engine()
{
}

void Engine::handleInput()
{

}

void Engine::update()
{
	m_window->update();
}

void Engine::render()
{
	m_window->beginDraw();

	m_window->endDraw();
}

Window* Engine::getWindow()
{
	return m_window.get();
}