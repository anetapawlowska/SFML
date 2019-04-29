#pragma once
#include "State.h"
#include <memory>

class Player;
class Enemies;
class Bullets;

class GameState : public State
{
public:
	GameState();
	~GameState();

	void handleInput(sf::RenderWindow* window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow* window) override;

	void onEnter() override;
	void onLeave() override;

	void start();
	void checkCollisions();
	bool isCollision(sf::RectangleShape first, sf::RectangleShape second) const;

private:
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Bullets> m_playersBullets;
	std::unique_ptr<Enemies> m_enemies;
	std::unique_ptr<Bullets> m_enemiesBullets;
};

