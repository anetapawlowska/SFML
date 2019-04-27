#pragma once

#include "SFML\Graphics.hpp"
#include "Window.h"
#include "EventManager.h"

class StateManager;

class BaseState
{
	friend class StateManager;

public:
	BaseState(StateManager* stateManager) : m_stateMgr{ stateManager }, m_transparent{ false }, m_transcendent{ false }{}
	virtual ~BaseState(){ }

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time& time) = 0;
	virtual void draw() = 0;

	void setTransparent(const bool& transparent)
	{
		m_transparent = transparent;
	}
	bool isTransparent() const
	{
		return m_transparent;
	}
	void setTranscendent(const bool& transcendence)
	{
		m_transcendent = transcendence;
	}
	bool isTranscendent() const
	{
		return m_transcendent;
	}
	
	StateManager* getStateManager()
	{
		return m_stateMgr;
	}

protected:
	StateManager* m_stateMgr;
	bool m_transparent;
	bool m_transcendent;
};

enum class StateType
{
	Intro = 1,
	MainMenu,
	Game,
	Paused,
	GameOver,
	Credits
};

struct SharedContext
{
	SharedContext() : m_wind(nullptr), m_eventManager(nullptr){}
	Window* m_wind;
	EventManager* m_eventManager;
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
public:
	StateManager(SharedContext* shared);
	~StateManager();

	void update(const sf::Time& time);
	void draw();

	void processRequests();

	SharedContext* getContext();
	bool hasState(const StateType& type);

	void switchTo(const StateType& type);
	void remove(const StateType& type);

private:
	void createState(const StateType& type);
	void removeState(const StateType& type);

	template<class T>
	void registerState(const StateType& type) {...}

	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};

