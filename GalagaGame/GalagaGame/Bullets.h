#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class Bullets
{
public:
	Bullets(sf::Vector2f windowSize);
	virtual ~Bullets();

	void update();
	void render(sf::RenderWindow* window);

	void add(sf::Vector2f position);
	std::vector<sf::Vector2f>& getBulletsPositions();
	void start();
	void remove(sf::Vector2f pos);

	virtual float getStep() const = 0;

private:
	std::vector<sf::Vector2f> m_bullets;
	sf::Vector2f m_windowSize;
	sf::Vector2f m_size{ 4.0f, 4.0f };
};

