#include "stdafx.h"
#include "Window.h"


Window::Window()
{
	m_window.create({ 640, 480, 32 }, "Galaga", sf::Style::Default);
}

Window::~Window()
{
	m_window.close();
}

void Window::beginDraw() 
{
	m_window.clear(sf::Color::Black);
}

void Window::endDraw() 
{
	m_window.display();
}

void Window::update() 
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_isDone = true;
	}
}

bool Window::isDone() const 
{
	return m_isDone;
}

sf::RenderWindow* Window::getRenderWindow()
{
	return &m_window;
}