#pragma once
#include <SFML\Graphics.hpp>

class Enemy
{
public:
	Enemy(sf::Vector2f windowSize, sf::Vector2f size, sf::Color color, sf::Vector2f position);
	~Enemy();

	enum class EnemyType
	{
		shooter,
		nonShooter
	};

	enum class Action
	{
		sway,
		attack,
		goBack
	};

	void update(float deltaTime);
	void render(sf::RenderWindow* window);
	void changeStep(sf::Vector2f step);
	sf::Vector2f getPosition() const;
	sf::Vector2f getStep() const;
	Action getAction() const;
	void attack(sf::Vector2f step);

private:
	sf::Color m_color;
	sf::Vector2f m_windowSize;
	sf::Vector2f m_size;
	sf::Vector2f m_step{ 0.0f, 0.0f };
	sf::Vector2f m_position;
	sf::Vector2f m_startPosition;
	EnemyType m_type{EnemyType::shooter };
	Action m_action{ Action::sway };
};

