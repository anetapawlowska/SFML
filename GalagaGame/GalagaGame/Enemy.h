#pragma once
#include <SFML\Graphics.hpp>

class Bullets;

class Enemy
{
public:
	enum class Action
	{
		stayStill,
		attack,
		goBack
	};
	
	explicit Enemy( Bullets* bullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color color, sf::Vector2f position);
	~Enemy();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	sf::RectangleShape& getShape();
	sf::Vector2f getPosition() const;
	Action getAction() const;
	void attack(sf::Vector2f step);
	virtual void shoot();

private:
	Bullets* m_bullets;
	sf::RectangleShape m_shape;
	sf::Vector2u m_windowSize;
	sf::Vector2f m_step{ 0.0f, 0.0f };
	sf::Vector2f m_startPosition;
	Action m_action{ Action::stayStill };
};

