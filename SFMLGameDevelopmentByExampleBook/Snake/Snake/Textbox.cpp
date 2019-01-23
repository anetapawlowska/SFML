#include "Textbox.h"


Textbox::Textbox()
{
	setup(5, 9, 200, sf::Vector2f(0, 0));
}


Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox()
{
}

void Textbox::setup(int visible, int charSize, int width, sf::Vector2f screenPos)
{
	m_numVisible = visible;
	sf::Vector2f offset(2.0f, 2.0f);
	
	m_font.loadFromFile("arial.ttf");
	m_content.setFont(m_font);
	m_content.setString("");
	m_content.setCharacterSize(charSize);
	m_content.setFillColor(sf::Color::White);
	m_content.setPosition(screenPos + offset);

	m_backdrop.setSize(sf::Vector2f(width, (visible * (charSize * 1.2f))));
	m_backdrop.setFillColor(sf::Color(90, 90, 90, 90));
	m_backdrop.setPosition(screenPos);
}

void Textbox::add(std::string message)
{
	m_messages.push_back(message);
	if (m_messages.size() < 6)
		return;
	m_messages.erase(m_messages.begin());
}

void Textbox::clear()
{
	m_messages.clear();
}

void Textbox::render(sf::RenderWindow& wind)
{
	std::string content;

	for (auto &msg : m_messages)
		content.append(msg + "\n");

	if (content != "")
	{
		m_content.setString(content);
		wind.draw(m_backdrop);
		wind.draw(m_content);
	}
}