#include "Window.h"


Window::Window()
{
	setup("Window", sf::Vector2u{640, 480});
}

Window::Window(const std::string& title, const sf::Vector2u& size)
{
	setup(title, size);
}


Window::~Window()
{
	destroy();
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
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
			toggleFullScreen();
	}
}

bool Window::isDone() const 
{
	return m_isDone;
}

bool Window::isFullScreen() const 
{
	return m_isFullScreen;
}

sf::Vector2u Window::getWindowSize() const 
{
	return m_size;
}

void Window::toggleFullScreen() 
{
	m_isFullScreen = !m_isFullScreen;
	destroy();
	create();
}

void Window::draw(sf::Drawable& drawable) 
{
	m_window.draw(drawable);
}

void Window::setup(const std::string& title, const sf::Vector2u& size) 
{
	m_title = title;
	m_size = size;
	m_isDone = false;
	m_isFullScreen = false;
	create();
}

void Window::destroy() 
{
	m_window.close();
}

void Window::create() 
{
	auto style = m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default;
	m_window.create({ m_size.x, m_size.y, 32 }, m_title, style);
}