#include "stdafx.h"
#include "Enemies.h"
#include <cstdlib>
#include <cmath>

Enemies::Enemies(EnemiesBullets* enemiesBullets, sf::Vector2f windowSize) : m_windowSize{ windowSize }, m_bullets { enemiesBullets }
{
	m_size = { 16.0f, 16.0f };
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
		//if (enemy.getAction() == Enemy::Action::sway && rand() % 100 == 0)
		//	attack(enemy);
				
		enemy.update(deltaTime);
	}

	for (auto& enemy : m_enemies)
		if (enemy.getAction() == Enemy::Action::attack && rand() % 20 == 0)
			shoot(enemy.getPosition());

	/*++m_sways;
	if (m_sways == m_swayInOneDirection)
	{
		for (auto& enemy : m_enemies)
		{
			const auto step = enemy.getStep();
			enemy.changeStep({ -1 * step.x, 0.0f });
		}
		m_sways = 0;
	}*/
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
			m_enemies.push_back(Enemy(m_windowSize, sf::Vector2f{ 16.0f, 16.0f }, sf::Color::Blue, position));
		}

	attack(m_enemies[0]);
}

void Enemies::shoot(sf::Vector2f position)
{
	const auto bulletsSize = m_bullets->getSize();
	const float x = position.x + m_size.x / 2 - bulletsSize.x / 2;
	const float y = position.y + m_size.y;
	m_bullets->add({ x,y });
}

void Enemies::start()
{
	m_enemies.clear();
	add();
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

void Enemies::attack(Enemy& enemy)
{
	const float endPosX = rand() % static_cast<int>(m_windowSize.x - 16);
	const auto startPos = enemy.getPosition();

	const unsigned numOfSteps = std::ceil((m_windowSize.y - startPos.y) / m_step);

	const float stepX = (endPosX - startPos.x) / numOfSteps;

	enemy.attack({ stepX, m_step });
}