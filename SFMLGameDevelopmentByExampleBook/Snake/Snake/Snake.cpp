#include "Snake.h"


Snake::Snake(int blockSize)
{
	m_size = blockSize;
	m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	reset();
}


Snake::~Snake()
{
}

void Snake::reset()
{
	m_snakeBody.clear();

	m_snakeBody.push_back(SnakeSegment(5, 7));
	m_snakeBody.push_back(SnakeSegment(5, 6));
	m_snakeBody.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None);
	m_speed = 15;
	m_lives = 3;
	m_score = 0;
	m_lost = false;
}

void Snake::setDirection(Direction dir)
{ 
	m_dir = dir;
}

Direction Snake::getDirection() const
{
	return m_dir;
}

int Snake::getSpeed() const
{
	return m_speed;
}

sf::Vector2i Snake::getPosition() const
{
	return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::getLives() const
{
	return m_lives;
}

int Snake::getScore() const
{
	return m_score;
}

void Snake::increaseScore()
{
	m_score += 10;
}

bool Snake::hasLost()
{
	return m_lost;
}

void Snake::lose()
{
	m_lost = true;
}

void Snake::toggleLost()
{
	m_lost = !m_lost;
}

void Snake::extend()
{
	if (m_snakeBody.empty())
		return;

	SnakeSegment& tailHead = m_snakeBody[m_snakeBody.size() - 1];
	if (m_snakeBody.size() > 1)
	{
		SnakeSegment& tailBone = m_snakeBody[m_snakeBody.size() - 2];
		if (tailHead.position.x == tailBone.position.x)
		{
			if (tailHead.position.y > tailBone.position.y)
				m_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
			else
				m_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
		}
		else if (tailHead.position.y == tailBone.position.y)
		{
			if (tailHead.position.x > tailBone.position.x)
				m_snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
			else
				m_snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
		}
	}
	else
	{
		if (m_dir == Direction::Up)
			m_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y + 1));
		else if (m_dir == Direction::Down)
			m_snakeBody.push_back(SnakeSegment(tailHead.position.x, tailHead.position.y - 1));
		else if (m_dir == Direction::Left)
			m_snakeBody.push_back(SnakeSegment(tailHead.position.x + 1, tailHead.position.y));
		else if (m_dir == Direction::Right)
			m_snakeBody.push_back(SnakeSegment(tailHead.position.x - 1, tailHead.position.y));
	}
}

void Snake::tick()
{
	if (m_snakeBody.empty() || m_dir == Direction::None)
		return;
	move();
	checkCollision();
}

void Snake::move()
{
	for (int i = m_snakeBody.size() - 1; i > 0; --i)
		m_snakeBody[i].position = m_snakeBody[i - 1].position;
	if (m_dir == Direction::Left)
		--m_snakeBody[0].position.x;
	else if (m_dir == Direction::Right)
		++m_snakeBody[0].position.x;
	else if (m_dir == Direction::Up)
		--m_snakeBody[0].position.y;
	else if (m_dir == Direction::Down)
		++m_snakeBody[0].position.y;
}

void Snake::checkCollision()
{
	if (m_snakeBody.size() < 5)
		return;
	SnakeSegment& head = m_snakeBody.front();
	for (auto it = m_snakeBody.begin() + 1; it != m_snakeBody.end(); ++it)
	{
		if (it->position == head.position)
		{
			int segments = m_snakeBody.end() - it;
			cut(segments);
			break;
		}
	}
}

void Snake::cut(int segments)
{
	for (int i = 0; i < segments; ++i)
		m_snakeBody.pop_back();
	--m_lives;
	if (!m_lives)
		lose();
}

void Snake::render(sf::RenderWindow& window)
{
	if (m_snakeBody.empty())
		return;
	auto head = m_snakeBody.begin();
	m_bodyRect.setFillColor(sf::Color::Yellow);
	m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
	window.draw(m_bodyRect);
	
	m_bodyRect.setFillColor(sf::Color::Green);
	for (auto it = m_snakeBody.begin() + 1;  it != m_snakeBody.end(); ++it)
	{
		m_bodyRect.setPosition(it->position.x * m_size, it->position.y * m_size);
		window.draw(m_bodyRect);
	}


}











