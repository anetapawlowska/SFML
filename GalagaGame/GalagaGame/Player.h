#pragma once
#include "SFML\Graphics.hpp"

class Bullets;

class Player
{
public:
	Player(Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, float step, sf::Color color);
	~Player();

	void update(float deltaTime);
	void render(sf::RenderWindow* renderWindow);

	void moveLeft();
	void moveRight();
	void shoot();
	sf::RectangleShape& getPlayerShape();
	void start();

private:
	sf::RectangleShape m_player;
	Bullets* m_bullets;
	sf::Vector2u m_windowSize;
	sf::Vector2f m_startPosition;
	const sf::Vector2f m_size;
	const float m_step;
};

