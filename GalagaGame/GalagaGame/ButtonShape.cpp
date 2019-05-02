#include "stdafx.h"
#include "ButtonShape.h"


ButtonShape::ButtonShape(sf::Vector2f size, sf::Color color, sf::Vector2f position, std::string text )
{
	m_shape.setSize(size);
	m_shape.setFillColor(color);
	sf::FloatRect shapeRect = m_shape.getLocalBounds();
	m_shape.setOrigin(shapeRect.left + shapeRect.width / 2.0f, shapeRect.top + shapeRect.height / 2.0f);
	m_shape.setPosition(position);
	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setCharacterSize(15);
	m_text.setFillColor(sf::Color::White);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_text.setPosition(position);
}


ButtonShape::~ButtonShape()
{
}

void ButtonShape::render(sf::RenderWindow* window)
{
	window->draw(m_shape);
	window->draw(m_text);
}

bool ButtonShape::isClicked(float x, float y) const
{
	return m_shape.getGlobalBounds().contains(x, y);
}