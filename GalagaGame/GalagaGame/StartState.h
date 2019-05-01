#pragma once
#include "State.h"
#include <memory>

class StateManager;
class ButtonShape;

class StartState : public State
{
public:
	explicit StartState(StateManager* stateManager);
	~StartState();

	 void handleInput(sf::RenderWindow* window) override;
	 void update(float deltaTime) override;
	 void render(sf::RenderWindow* window) override;

	 void onEnter() override;
	 void onLeave() override;


private:
	std::unique_ptr<ButtonShape> m_button;
	StateManager* m_stateManager;
};

