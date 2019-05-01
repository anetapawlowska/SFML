#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class Bullets
{
public:
	explicit Bullets(sf::Vector2u windowSize, sf::Vector2f size, sf::Color color);
	virtual ~Bullets();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void add(sf::Vector2f position);
	std::vector<sf::Vector2f>& getBulletsPositions();
	void clear();
	void remove(sf::Vector2f pos);
	sf::Vector2f getSize() const;
	void setStep(float step);

private:
	std::vector<sf::Vector2f> m_bullets;
	
	const sf::Vector2u m_windowSize;
	const sf::Vector2f m_size;
	float m_step{};
	const sf::Color m_color;
};

