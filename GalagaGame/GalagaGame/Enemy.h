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

	explicit Enemy(sf::Vector2u windowSize, sf::Vector2f size, sf::Color color, sf::Vector2f position, EnemyType type);
	~Enemy();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	sf::RectangleShape& getShape();
	sf::Vector2f getPosition() const;
	Action getAction() const;
	EnemyType getType() const;
	void attack(sf::Vector2f step);

private:
	sf::RectangleShape m_shape;
	sf::Vector2u m_windowSize;
	sf::Vector2f m_step{ 0.0f, 0.0f };
	sf::Vector2f m_startPosition;
	EnemyType m_type;
	Action m_action{ Action::stayStill };
};

