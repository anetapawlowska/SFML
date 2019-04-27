#pragma once

#include "StateManager.h"

class StateIntro : public BaseState
{
public:
	StateIntro() = default;
	~StateIntro() = default;
	
	void onCreate() override;
	void onDestroy() override;
	void update(const sf::Time& time) override;
	void draw() override;
	void activate() override;
	void deactivate() override;

	void goToMainMenu(EventDetails* details);

private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Text m_text;
	sf::Font m_font;
	float m_timePassed;
};

