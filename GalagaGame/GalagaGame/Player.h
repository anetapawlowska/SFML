#pragma once
#include "SFML\Graphics.hpp"
#include "Helpers.h"

class PlayersBullets;

class Player
{
public:
	Player(PlayersBullets* bullets);
	~Player();

	void update();
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
};

