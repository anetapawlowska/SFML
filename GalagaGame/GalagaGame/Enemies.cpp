#include "stdafx.h"
#include "Enemies.h"
#include <cstdlib>
#include <cmath>

Enemies::Enemies(Bullets* enemiesBullets, sf::Vector2f windowSize, sf::Vector2f size, float step, sf::Color color) : m_windowSize{ windowSize },
m_bullets{ enemiesBullets }, m_size{ size }, m_step{step}, m_color{color}
{
}


Enemies::~Enemies()
{
}

void Enemies::update(float deltaTime)
{
	if (m_enemies.empty())
		return;

	for (auto& enemy : m_enemies)
	{
		if (enemy.getAction() == Enemy::Action::sway && rand() % ( 200 * m_enemies.size()) == 0)	
			enemy.attack({ 0.0f, m_step });
				
		enemy.update(deltaTime);
	}

	for (auto& enemy : m_enemies)
		if (enemy.getAction() == Enemy::Action::attack && rand() % 20 == 0)
			shoot(enemy.getPosition());
}

void Enemies::render(sf::RenderWindow* window) 
{
	for (auto& enemy : m_enemies)
		enemy.render(window);
}

void Enemies::add()
{
	const unsigned numOfRows = 3;
	const float fromWall = 50.f;
	const float spaces = 8.f;

	const unsigned inRow = (m_windowSize.x - 2 * fromWall + spaces) / (m_size.x + spaces);
	const float startPoint = (m_windowSize.x - inRow * m_size.x - (inRow - 1) * spaces) / 2;

	for (unsigned row = 0; row < numOfRows; ++row)
		for (unsigned i = 0; i < inRow; ++i)
		{
			sf::Vector2f position{ startPoint + i * (m_size.x + spaces), 32.0f + row * (m_size.y + spaces) };
			m_enemies.push_back(Enemy(m_windowSize, m_size, m_color, position));
		}
}

void Enemies::shoot(sf::Vector2f position)
{
	const auto bulletsSize = m_bullets->getSize();
	const float x = position.x + m_size.x / 2 - bulletsSize.x / 2;
	const float y = position.y + m_size.y;
	m_bullets->add({ x,y });
}

void Enemies::clear()
{
	m_enemies.clear();
}

std::vector<Enemy>& Enemies::getEnemies()
{
	return m_enemies;
}

void Enemies::killed(sf::Vector2f pos)
{
	auto it = std::find_if(begin(m_enemies), end(m_enemies), [pos](auto enemy) {return enemy.getPosition() == pos; });
	if (it != end(m_enemies))
		m_enemies.erase(it);
}
