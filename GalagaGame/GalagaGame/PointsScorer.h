#pragma once
#include <SFML\Graphics.hpp>
#include "Enemy.h"
#include "SharedContext.h"

class PointsScorer
{
public:
	PointsScorer(SharedContext* sharedContext);
	~PointsScorer();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void addPointsForKill(Enemy::Action action);
	void resetScore();

private:
	void setScoreText();

	// ===== dummy logic ======
	unsigned getPointsForKill(Enemy::Action action) const;
	// ========================

	SharedContext* m_sharedContext;
	sf::Text m_pointsText;
	sf::Font m_font;
};

