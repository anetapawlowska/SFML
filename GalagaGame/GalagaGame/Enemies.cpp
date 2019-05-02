#include "stdafx.h"
#include "Enemies.h"

#include <cstdlib>
#include <cmath>

#include "Bullets.h"
#include "Enemy.h"
#include "NonShooterEnemy.h"

Enemies::Enemies(Bullets* enemiesBullets, sf::Vector2u windowSize, sf::Vector2f size, sf::Color shooterColor, sf::Color nonShooterColor) : m_windowSize{ windowSize },
m_bullets{ enemiesBullets }, m_enemySize{ size }, m_shooterColor{ shooterColor }, m_nonShooterColor{ nonShooterColor }
{
}


Enemies::~Enemies()
{
}

void Enemies::update(float deltaTime)
{
	for (auto& enemy : m_enemies)
	{
		if (enemy->getAction() == Enemy::Action::stayStill && shouldGoAttack())
			enemy->attack({ 0.0f, m_step });
		else if (enemy->getAction() == Enemy::Action::attack && shouldFire())
			enemy->shoot();

		enemy->update(deltaTime);
	}
}

void Enemies::render(sf::RenderWindow* window) 
{
	for (auto& enemy : m_enemies)
		enemy->render(window);
}

void Enemies::clear()
{
	m_enemies.clear();
}

Enemies::EnemiesInfo& Enemies::getEnemies()
{
	return m_enemies;
}

void Enemies::killed(Enemies::EnemiesInfo::iterator enemyIt)
{
	if (enemyIt != end(m_enemies))
		m_enemies.erase(enemyIt);
}

void Enemies::everybodyGoBack()
{
	for (auto& enemy : m_enemies)
		enemy->goBack();
}

// ========================== dummy logic ===============================

void Enemies::add(unsigned numOfRows, float step)
{
	m_step = step;

	const float fromCeiling = 32.0f;
	const float fromWall = 50.f;
	const float spaces = 8.f;

	const unsigned inRow = static_cast<unsigned>((m_windowSize.x - 2 * fromWall + spaces) / (m_enemySize.x + spaces));
	const float startPoint = (m_windowSize.x - inRow * m_enemySize.x - (inRow - 1) * spaces) / 2;

	const auto getStartPosition = [=](int reel, int row ) {return sf::Vector2f{ startPoint + reel * (m_enemySize.x + spaces), fromCeiling + row * (m_enemySize.y + spaces) }; };
	const auto posYOffset = getStartPosition(0, numOfRows - 1).y + m_enemySize.y;

	m_enemies.reserve(numOfRows * inRow);

	for (unsigned row = 0; row < numOfRows; row += 2)
		for (unsigned reel = 0; reel < inRow; ++reel)
		{
			const auto startPos = getStartPosition(reel ,row);
			m_enemies.push_back(std::make_unique<Enemy>(m_bullets, m_windowSize, m_enemySize, m_shooterColor, 
				startPos, sf::Vector2f{ startPos.x, startPos.y - posYOffset }, sf::Vector2f{ 0.0f, m_step }));
		}

	for (unsigned row = 1; row < numOfRows; row += 2)
		for (unsigned reel = 0; reel < inRow; ++reel)
		{
			const auto startPos = getStartPosition(reel ,row);
			m_enemies.push_back(std::make_unique<NonShooterEnemy>(m_bullets, m_windowSize, m_enemySize, m_nonShooterColor, 
				startPos, sf::Vector2f{ startPos.x, startPos.y - posYOffset }, sf::Vector2f{ 0.0f, m_step }));
		}
}

bool Enemies::shouldGoAttack() const
{
	return rand() % (100 * m_enemies.size()) == 0;
}

bool Enemies::shouldFire() const
{
	return rand() % 20 == 0;
}