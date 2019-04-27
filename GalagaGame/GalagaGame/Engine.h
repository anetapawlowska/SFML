#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Player.h"
#include "Enemies.h"
#include "EnemiesBullets.h"

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

	Window* getWindow();

private:
	std::unique_ptr<Window> m_window;
	Player m_player;
	Enemies m_enemies;
	EnemiesBullets m_enemiesBullets;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};