#pragma once
#include <SFML\Graphics.hpp>

class Stars
{
public:
	Stars(float step);
	~Stars();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::View m_view;

	float m_step;
};

