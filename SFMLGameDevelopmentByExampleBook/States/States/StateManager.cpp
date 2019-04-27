#include "StateManager.h"
#include "StateIntro.h"

template<class T>
void registerState(const StateType& type)
{
	m_stateFactory[type] = [this]()->BaseState*
	{
		return new T(this);
	};
}

StateManager::StateManager(SharedContext* shared) : m_shared{shared}
{
	registerState<StateIntro>(StateType::Intro);
	//registerState<State_MainMenu>(StateType::MainMenu);
	//registerState<State_Game>(StateType::Game);
	//registerState<State_Paused>(StateType::Paused);
}


StateManager::~StateManager()
{
	for (auto &state : m_states)
	{
		state.second->onDestroy();
		delete state.second;
	}
}

void StateManager::draw()
{
	if (m_states.empty())
		return;
	if (m_states.back().second->isTransparent() && m_states.size() > 1)
	{
		auto it = m_states.end();
		while (it != m_states.begin())
		{
			if (it != m_states.end())
			{
				if (!it->second->isTransparent())
					break;
			}
			--it;
		}
		for (; it != m_states.end(); ++it)
			it->second->draw();
	}
	else
		m_states.back().second->draw();
}

void StateManager::update(const sf::Time& time)
{
	if (m_states.empty())
		return;
	if (m_states.back().second->isTranscendent() && m_states.size() > 1)
	{
		auto it = m_states.end();
		while (it != m_states.begin())
		{
			if (it != m_states.end() && !it->second->isTranscendent())
				break;
			--it;
		}
		for (; it != m_states.end(); ++it)
			it->second->update(time);
	}
	else
		m_states.back().second->update(time);
}

SharedContext* StateManager::getContext()
{
	return m_shared;
}

bool StateManager::hasState(const StateType& type)
{
	for (auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		if (it->first == type)
		{
			auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), type);
			if (removed == m_toRemove.end())
				return true;
		}
	}
	return false;
}

void StateManager::remove(const StateType& type)
{
	m_toRemove.push_back(type);
}

void StateManager::processRequests()
{
	while (m_toRemove.begin() != m_toRemove.end())
	{
		removeState(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

void StateManager::switchTo(const StateType& type)
{
	//m_shared->m_eventManager->setCurrentState(type);
	for (auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		if (it->first == type)
		{
			m_states.back().second->deactivate();
			StateType tmp_type = it->first;
			BaseState* tmp_state = it->second;
			m_states.erase(it);
			m_states.emplace_back(tmp_type, tmp_state);
			tmp_state->activate();
			return;
		}
	}
	if (!m_states.empty())
		m_states.back().second->deactivate();
	createState(type);
	m_states.back().second->activate();
}

void StateManager::createState(const StateType& type)
{
	auto newState = m_stateFactory.find(type);
	if (newState == m_stateFactory.end())
		return;
	BaseState* state = newState->second();
	m_states.emplace_back(type, state);
	state->onCreate();
}

void StateManager::removeState(const StateType& type)
{
	for (auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		if (it->first == type)
		{
			it->second->onDestroy();
			delete it->second;
			m_states.erase(it);
			return;
		}
	}
}


