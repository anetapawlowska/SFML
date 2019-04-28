#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.h"
#include "Enemies.h"
#include "EnemiesBullets.h"
#include "PlayersBullets.h"

class Window;

class Engine
{
public:
	Engine();
	~Engine();

	void handleInput();
	void update();
	void render();
	sf::Time getElapsed() const;
	void restartClock();

	void start();

	void checkCollisions();
	bool isCollision(sf::RectangleShape first, sf::RectangleShape second) const;

	sf::RenderWindow* getWindow();

private:
	sf::RenderWindow m_window;
	Player m_player;
	PlayersBullets m_playersBullets;
	Enemies m_enemies;
	EnemiesBullets m_enemiesBullets;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};