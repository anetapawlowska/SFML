#pragma once
#include <SFML\Graphics.hpp>

class ButtonShape
{
public:
	explicit ButtonShape(sf::Vector2f size, sf::Color color, sf::Vector2f position, std::string text);
	~ButtonShape();

	bool isClicked(float x, float y) const;
	void render(sf::RenderWindow* window);

private:
	sf::RectangleShape m_shape;
	sf::Text m_text;
	sf::Font m_font;
};

