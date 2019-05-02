#include "stdafx.h"
#include "Stars.h"


Stars::Stars(float step) : m_step{step}
{
	m_texture.loadFromFile("stars.png");
	m_texture.setRepeated(true);
	auto textureSize = m_texture.getSize();
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect( 0, 0, textureSize.x, textureSize.y * 2 + 20 ));
	m_view.reset(sf::FloatRect(0.0f, 0.0f, static_cast<float>(textureSize.x), static_cast<float>(textureSize.y)));
	m_view.setCenter({ textureSize.x / 2.0f, textureSize.y / 2.0f });
	m_view.rotate(180.0f);
}


Stars::~Stars()
{
}


void Stars::update(float deltaTime)
{
	sf::Vector2f center{ m_view.getCenter().x, m_view.getCenter().y };
	const sf::Vector2u textureSize = m_texture.getSize();
	if (center.y > 1.5f * textureSize.y)
		center.y -= textureSize.y;
	m_view.setCenter(center.x, center.y + m_step);
}

void Stars::render(sf::RenderWindow* window)
{
	window->setView(m_view);
	window->draw(m_sprite);
	window->setView(window->getDefaultView());
}