#pragma once
#include "State.h"

class StateManager;

class GameOverState : public State
{
public:
	GameOverState(StateManager* stateManager);
	~GameOverState();

	void handleInput(sf::RenderWindow* window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow* window) override;

	void onEnter() override;
	void onLeave() override;

private:
	void setText();

	sf::Text m_text;
	sf::Font m_font;

	StateManager * m_stateManager;
};

