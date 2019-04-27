#pragma once

#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <functional>

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1,
	Mouse,
	Joystick
};

struct EventInfo
{
	EventInfo()
	{
		code = 0;
	}
	EventInfo(int event)
	{
		code = event;
	}
	union
	{
		int code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
	EventDetails(const std::string& bindName) : name(bindName)
	{
		clear();
	}
	std::string name;
	sf::Vector2i size;
	sf::Uint32 textEntered;
	sf::Vector2i mouse;
	int mouseWheelDelta;
	int keyCode;

	void clear()
	{
		size = sf::Vector2i(0, 0);
		textEntered = 0;
		mouse = sf::Vector2i(0, 0);
		mouseWheelDelta = 0;
		keyCode = -1;
	}
};

struct Binding
{
	Binding(const std::string& name) : name(name), details(name), numOfHappeningEvents(0) {}
	
	void BindEvent(EventType type, EventInfo info = EventInfo())
	{
		events.emplace_back(type, info);
	}

	Events events;
	std::string name;
	int numOfHappeningEvents;
	EventDetails details;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map < std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool addBinding(Binding *binding);
	bool removeBinding(std::string name);
	void setFocus(bool focus);

	template<class T>
	bool addCallback(StateType state, const std::string& name, void(T::*func)(EventDetails*), T* instance)
	{
		auto it = m_callbacks.emplace(state, CallbackContainer()).first;
		auto temp = std::bind(func, instance, std::placeholders::_1);
		return it->second.emplace(name, temp).second;
	}

	bool removeCallback(StateType state, const std::string& name)
	{
		auto it = m_callbacks.find(state);
		if (it == m_callbacks.end())
			return false;
		auto it2 = it->second.find(name);
		if (it2 == it->second.end())
			return false;
		it->second.erase(name);
		return true;
	}

	void handleEvent(sf::Event& event);
	void update();

	sf::Vector2i getMousePos(sf::RenderWindow* wind = nullptr)
	{
		return (wind ? sf::Mouse::getPosition(*wind) : sf::Mouse::getPosition());
	}

private:
	void loadBindings();
	
	Bindings m_bindings;
	Callbacks m_callbacks;
	StateType m_currentState;
	bool m_hasFocus;
};

