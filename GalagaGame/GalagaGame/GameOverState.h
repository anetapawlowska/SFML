#pragma once
#include "State.h"
#include <memory>

class StateManager;
class ButtonShape;

class GameOverState : public State
{
public:
	explicit GameOverState(StateManager* stateManager);
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
	std::unique_ptr<ButtonShape> m_startButton;
	std::unique_ptr<ButtonShape> m_endButton;
	StateManager * m_stateManager;
};

