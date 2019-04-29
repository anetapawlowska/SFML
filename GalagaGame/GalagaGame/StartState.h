#pragma once
#include "State.h"

class StateManager;

class StartState : public State
{
public:
	StartState(StateManager* stateManager);
	~StartState();

	 void handleInput(sf::RenderWindow* window) override;
	 void update(float deltaTime) override;
	 void render(sf::RenderWindow* window) override;

	 void onEnter() override;
	 void onLeave() override;

private:
	sf::Text m_text;
	sf::Font m_font;
	StateManager* m_stateManager;
};

