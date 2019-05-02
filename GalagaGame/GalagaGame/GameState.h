#pragma once
#include "State.h"
#include <memory>
#include "Enemy.h"
#include "Enemies.h"

class Player;
class Bullets;
class StateManager;
class PointsScorer;

class GameState : public State
{
public:
	explicit GameState(StateManager* stateManager);
	~GameState();

	void handleInput(sf::RenderWindow* window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow* window) override;

	void onEnter() override;
	void onLeave() override;


private:
	enum class PlayersDirection
	{
		none,
		right,
		left
	};

	void start();
	void checkCollisions();
	bool isCollision(sf::RectangleShape first, sf::RectangleShape second) const;
	void killMe();
	void killTheEnemy(Enemies::EnemiesInfo::iterator enemyIt, sf::Vector2f bulletPos);
	void nextLevel();
	void keyPressed(sf::Keyboard::Key key);
	void keyReleased(sf::Keyboard::Key key);
	void checkPlayersMove();
	void setLivesText();
	void clearPlayer();

	// ===== dummy logic ======
	float getPlayersStep() const;
	float getBulletsStep() const;
	unsigned getNumOfEnemiesRows() const;
	float getEnemiesSteps() const;
	// ========================

	StateManager* m_stateManager;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Bullets> m_playersBullets;
	std::unique_ptr<Enemies> m_enemies;
	std::unique_ptr<Bullets> m_enemiesBullets;
	std::unique_ptr<PointsScorer> m_pointsScorer;

	unsigned m_keyPressedCounter{0};
	bool m_isKeyPressed{ false };
	PlayersDirection m_playersDirection{ PlayersDirection::none };

	sf::Font m_font;
	unsigned m_lives{};
	sf::Text m_livesText;
};

