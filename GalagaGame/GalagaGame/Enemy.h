#pragma once
#include <SFML\Graphics.hpp>

class Enemy
{
public:
	enum class EnemyType
	{
		shooter,
		nonShooter
	};

	enum class Action
	{
		stayStill,
		attack,
		goBack
	};

	Enemy(sf::Vector2u windowSize, sf::Vector2f size, sf::Color color, sf::Vector2f position, EnemyType type);
	~Enemy();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);
	void changeStep(sf::Vector2f step);
	sf::Vector2f getPosition() const;
	sf::Vector2f getStep() const;
	Action getAction() const;
	EnemyType getType() const;
	void attack(sf::Vector2f step);

	sf::RectangleShape& getShape();

private:
	sf::RectangleShape m_shape;
	sf::Vector2u m_windowSize;
	sf::Vector2f m_step{ 0.0f, 0.0f };
	sf::Vector2f m_position;
	sf::Vector2f m_startPosition;
	EnemyType m_type;
	Action m_action{ Action::stayStill };
};

