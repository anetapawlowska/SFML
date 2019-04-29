#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Player;
class Enemies;
class Bullets;

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
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Bullets> m_playersBullets;
	std::unique_ptr<Enemies> m_enemies;
	std::unique_ptr<Bullets> m_enemiesBullets;

	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Time m_elapsed;
};