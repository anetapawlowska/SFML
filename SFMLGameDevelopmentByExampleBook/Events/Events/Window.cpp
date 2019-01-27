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

EventManager* Window::getEventManager()
{
	return &m_eventManager;
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
		if (event.type == sf::Event::LostFocus)
		{
			m_isFocused = false;
			m_eventManager.setFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_isFocused = true;
		}
		if (m_isFocused)
			m_eventManager.handleEvent(event);
	}
	m_eventManager.update();
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

void Window::toggleFullScreen(EventDetails* details)
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
	m_isFocused = true;
	create();
	m_eventManager.addCallback("Fullscreen_toggle", &Window::toggleFullScreen, this);
	m_eventManager.addCallback("Window_close", &Window::close, this);
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

sf::RenderWindow* Window::getRenderWindow()
{
	return &m_window;
}

void Window::close(EventDetails* details)
{
	m_isDone = true;
}

