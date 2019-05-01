#pragma once
#include <SFML\Graphics.hpp>
#include <memory>

struct SharedContext;
class State;

class StateManager
{
public:
	explicit StateManager(SharedContext* shared);
	~StateManager();

	enum class States
	{
		Start,
		Game,
		GameOver
	};

	void handleInput(sf::RenderWindow* window);
	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void setNextState(States state);

	SharedContext* getSharedContext();

protected:
	std::shared_ptr<State> m_currentState;
	std::map<States, std::shared_ptr<State>> m_states;
	SharedContext* m_shared;
};

