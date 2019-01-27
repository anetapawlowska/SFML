#include "EventManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

EventManager::EventManager() : m_hasFocus(true)
{

	loadBindings();
}


EventManager::~EventManager()
{
	for (auto &binding : m_bindings)
	{
		delete binding.second;
		binding.second = nullptr;
	}
}

void EventManager::setFocus(bool focus)
{
	m_hasFocus = focus;
}

bool EventManager::addBinding(Binding* binding)
{
	if (m_bindings.find(binding->name) != m_bindings.end())
		return false;
	return m_bindings.emplace(binding->name, binding).second;
}

bool EventManager::removeBinding(std::string name)
{
	auto it = m_bindings.find(name);
	if (it == m_bindings.end())
		return false;
	delete it->second;
	m_bindings.erase(it);
	return true;
}

void EventManager::handleEvent(sf::Event& event)
{
	for (auto &binding : m_bindings)
	{
		Binding* bind = binding.second;
		for (auto &bEvent : bind->events)
		{
			EventType sfmlEvent = (EventType)event.type;
			if (bEvent.first != sfmlEvent)
				continue;
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if (bEvent.second.code == event.key.code)
				{
					if (bind->details.keyCode != -1)
						bind->details.keyCode = bEvent.second.code;
					++(bind->numOfHappeningEvents);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
			{
				if (bEvent.second.code == event.mouseButton.button)
				{
					bind->details.mouse.x = event.mouseButton.x;
					bind->details.mouse.y = event.mouseButton.y;
					if (bind->details.keyCode != -1)
						bind->details.keyCode = bEvent.second.code;
					++(bind->numOfHappeningEvents);
					break;
				}
			}
			else
			{
				if (sfmlEvent == EventType::MouseWheel)
					bind->details.mouseWheelDelta = event.mouseWheel.delta;
				else if (sfmlEvent == EventType::WindowResized)
				{
					bind->details.size.x = event.size.width;
					bind->details.size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered)
					bind->details.textEntered = event.text.unicode;
				++(bind->numOfHappeningEvents);
			}

		}
	}
}

void EventManager::update()
{
	//if (!m_hasFocus)
	//	return;
	for (auto &binding : m_bindings)
	{
		Binding* bind = binding.second;
		for (auto &bEvent : bind->events)
		{
			switch (bEvent.first)
			{
			case(EventType::Keyboard) :
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(bEvent.second.code)))
				{
					if (bind->details.keyCode != -1)
						bind->details.keyCode = bEvent.second.code;
					++(bind->numOfHappeningEvents);
				}
				break;
			case(EventType::Mouse) :
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(bEvent.second.code)))
				{
					if (bind->details.keyCode != -1)
						bind->details.keyCode = bEvent.second.code;
					++(bind->numOfHappeningEvents);
				}
				break;
			case(EventType::Joystick) :
				break;
			}
		}

		if (bind->events.size() == bind->numOfHappeningEvents)
		{
			auto callIt = m_callbacks.find(bind->name);
			if (callIt != m_callbacks.end())
				callIt->second(&bind->details);
		}
		bind->numOfHappeningEvents = 0;
		bind->details.clear();
	}
}

void EventManager::loadBindings()
{
	std::string delimiter = ":";
	std::ifstream bindings;
	bindings.open("keys.cfg");
	if (!bindings.is_open())
	{
		std::cout << "! Failed loading keys.cgf." << std::endl;
		return;
	}
	std::string line;
	while (std::getline(bindings, line))
	{
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof())
		{
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos)
			{
				delete bind;
				bind = nullptr;
				break;
			}
			EventType type = EventType(stoi(keyval.substr(start, end - start)));
			int code = stoi(keyval.substr(end + delimiter.length(), keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.code = code;

			bind->BindEvent(type, eventInfo);
		}
		if (!addBinding(bind))
			delete bind;
		bind = nullptr;
	}
	bindings.close();
}