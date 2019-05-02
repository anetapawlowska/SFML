#include "stdafx.h"
#include "PointsScorer.h"
#include "Config.h"
#include "SharedContext.h"

PointsScorer::PointsScorer(SharedContext* sharedContext) : m_sharedContext{sharedContext}
{
	m_font.loadFromFile("arial.ttf");
	m_pointsText.setFont(m_font);
	m_pointsText.setCharacterSize(15);
	m_pointsText.setFillColor(sf::Color::White);
}


PointsScorer::~PointsScorer()
{
}

void PointsScorer::update(float deltaTime)
{}

void PointsScorer::render(sf::RenderWindow* window)
{
	window->draw(m_pointsText);
}

void PointsScorer::resetScore()
{
	m_sharedContext->points = 0;
	setScoreText();
}

void PointsScorer::addPointsForKill(Enemy::Action action)
{
	const unsigned points = getPointsForKill(action);
	m_sharedContext->points += points;
	setScoreText();
}

void PointsScorer::setScoreText()
{
	m_pointsText.setString("Score: " + std::to_string(m_sharedContext->points));
}

// ===== dummy logic ======
unsigned PointsScorer::getPointsForKill(Enemy::Action action) const
{
	const unsigned pointsForKill = 50;
	const unsigned pointsForAttacker = 75;
	return action == Enemy::Action::Attack ? pointsForAttacker : pointsForKill;
}