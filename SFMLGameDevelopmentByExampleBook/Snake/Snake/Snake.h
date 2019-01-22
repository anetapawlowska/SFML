#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

struct SnakeSegment
{
	SnakeSegment(int x, int y) : position{ x, y } {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction{None, Up, Down, Left, Right};

class Snake
{
public:
	Snake(int blockSize);
	~Snake();

	void setDirection(Direction dir);
	Direction getDirection() const;
	int getSpeed() const;
	sf::Vector2i getPosition() const;
	int getLives() const;
	int getScore() const;
	void increaseScore();
	bool hasLost();
	Direction getPhysicalDirection();

	void lose();
	void toggleLost();

	void extend();
	void reset();

	void move();
	void tick();
	void cut(int segments);
	void render(sf::RenderWindow& window);

private:
	void checkCollision();

	SnakeContainer m_snakeBody;
	int m_size;
	Direction m_dir;
	int m_speed;
	int m_lives;
	int m_score;
	bool m_lost;
	sf::RectangleShape m_bodyRect;

};

