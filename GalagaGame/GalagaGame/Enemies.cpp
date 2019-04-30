#include "stdafx.h"
#include "Enemies.h"
#include <cstdlib>
#include <cmath>

Enemies::Enemies(Bullets* enemiesBullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color shooterColor, sf::Color nonShooterColor) : m_windowSize{ windowSize },
m_bullets{ enemiesBullets }, m_size{ size }, m_shooterColor{ shooterColor }, m_nonShooterColor{ nonShooterColor }
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
		if (enemy.getAction() == Enemy::Action::stayStill && shouldAttack())	
			enemy.attack({ 0.0f, m_step });
				
		enemy.update(deltaTime);
	}

	for (auto& enemy : m_enemies)
		if (enemy.getAction() == Enemy::Action::attack && shouldShoot())
			shoot(enemy.getPosition());
}

void Enemies::render(sf::RenderWindow* window) 
{
	for (auto& enemy : m_enemies)
		enemy.render(window);
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

// ========================== dummy logic ===============================

void Enemies::add(unsigned numOfRows, float step)
{
	m_step = step;

	const float fromCeiling = 32.0f;
	const float fromWall = 50.f;
	const float spaces = 8.f;

	const unsigned inRow = static_cast<unsigned>((m_windowSize.x - 2 * fromWall + spaces) / (m_size.x + spaces));
	const float startPoint = (m_windowSize.x - inRow * m_size.x - (inRow - 1) * spaces) / 2;

	for (unsigned row = 0; row < numOfRows; ++row)
	{
		sf::Color color = row % 2 == 0 ? m_shooterColor : m_nonShooterColor;
		Enemy::EnemyType type = row % 2 == 0 ? Enemy::EnemyType::shooter : Enemy::EnemyType::nonShooter;
		for (unsigned i = 0; i < inRow; ++i)
		{
			sf::Vector2f position{ startPoint + i * (m_size.x + spaces), fromCeiling + row * (m_size.y + spaces) };
			m_enemies.push_back(Enemy(m_windowSize, m_size, color, position, type));
		}
	}
}

bool Enemies::shouldAttack() const
{
	return rand() % (100 * m_enemies.size()) == 0;
}

bool Enemies::shouldShoot() const
{
	return rand() % 20 == 0;
}