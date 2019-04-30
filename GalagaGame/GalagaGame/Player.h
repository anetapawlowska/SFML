#pragma once
#include <SFML\Graphics.hpp>

class Bullets;

class Player
{
public:
	Player(Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color color);
	~Player();

	void update(float deltaTime);
	void render(sf::RenderWindow* renderWindow);

	void start();
	void shoot();
	void move(float step);
	sf::RectangleShape& getPlayerShape();

private:
	sf::Vector2f getStartPosition() const;

	Bullets* m_bullets;

	sf::RectangleShape m_shape;
	sf::Vector2u m_windowSize;
};

