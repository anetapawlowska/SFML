#pragma once
#include "SFML\Graphics.hpp"

class PlayersBullets;

class Player
{
public:
	Player(PlayersBullets* bullets, sf::Vector2f windowSize);
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
	float step{ 8.0f };
	PlayersBullets* m_bullets;
	sf::Vector2f m_windowSize;
	sf::Vector2f m_startPosition;
	const sf::Vector2f m_size{ 16.0f, 16.0f };
};

