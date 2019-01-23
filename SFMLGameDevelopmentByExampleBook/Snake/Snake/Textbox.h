#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

using MessageContainer = std::vector<std::string>;

class Textbox
{
public:
	Textbox();
	Textbox(int visible, int charSize, int width, sf::Vector2f screenPos);
	~Textbox();

	void setup(int visible, int charSize, int width, sf::Vector2f screenPos);
	void add(std::string message);
	void clear();
	void render(sf::RenderWindow& wind);

private:
	MessageContainer m_messages;
	int m_numVisible;
	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};

