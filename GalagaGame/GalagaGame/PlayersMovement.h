#pragma once
#include <SFML\Graphics.hpp>

class PlayersMovement
{
public:
	enum class PlayersDirection
	{
		none,
		right,
		left
	};

	PlayersMovement(float playersStep, float playersMaxStep);
	~PlayersMovement();

	void update(float deltaTime);

	void keyPressed(sf::Keyboard::Key key);
	void keyReleased(sf::Keyboard::Key key);
	void clear();
	bool shouldMove() const;

	// ===== dummy logic ======
	float getStep() const;
	// ========================
private:

	unsigned m_keyPressedCounter{ 0 };
	bool m_isKeyPressed{ false };
	PlayersDirection m_playersDirection{ PlayersDirection::none };

	const float m_playersStep;
	const float m_playersMaxStep;
};

