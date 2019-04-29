#pragma once
#include "State.h"
#include <memory>
#include "Enemy.h"

class Player;
class Enemies;
class Bullets;
class StateManager;

class GameState : public State
{
public:
	GameState(StateManager* stateManager);
	~GameState();

	void handleInput(sf::RenderWindow* window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow* window) override;

	void onEnter() override;
	void onLeave() override;


private:
	void start();
	void checkCollisions();
	bool isCollision(sf::RectangleShape first, sf::RectangleShape second) const;
	void addPointsForKill(Enemy::Action action, Enemy::EnemyType type);
	void killed();
	void clear();

	StateManager * m_stateManager;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Bullets> m_playersBullets;
	std::unique_ptr<Enemies> m_enemies;
	std::unique_ptr<Bullets> m_enemiesBullets;

	sf::Text m_pointsText;
	sf::Font m_font;

	unsigned m_lives{ 3 };
	sf::Text m_livesText;
};

