#include "stdafx.h"
#include "GameState.h"

#include <SFML\Graphics.hpp>
#include <vector>

#include "Player.h"
#include "Enemies.h"
#include "Bullets.h"
#include "Enemy.h"
#include "StateManager.h"
#include "SharedContext.h"
#include "Config.h"
#include "PointsScorer.h"
#include "PlayersMovement.h"

GameState::GameState(StateManager* stateManager) : m_stateManager{ stateManager }
{
	Config* config = m_stateManager->getSharedContext()->config;

	m_playersBullets = std::make_unique<Bullets>(config->windowSize, config->bulletsSize, config->playersBulletsColor);
	m_player = std::make_unique<Player>(m_playersBullets.get(), config->windowSize, config->playersSize, config->playersColor);
	m_enemiesBullets = std::make_unique<Bullets>(config->windowSize, config->bulletsSize, config->enemiesBulletsColor);
	m_enemies = std::make_unique<Enemies>(m_enemiesBullets.get(), config->windowSize, config->enemiesSize, config->shootersColor, config->nonShootersColor);
	m_pointsScorer = std::make_unique<PointsScorer>(m_stateManager->getSharedContext());
	m_playersMovement = std::make_unique<PlayersMovement>(config->playersStep, config->playersMaxStep);

	m_font.loadFromFile("arial.ttf");
	m_livesText.setFont(m_font);
	m_livesText.setCharacterSize(15);
	m_livesText.setFillColor(sf::Color::White);
	m_livesText.setString("Lives: " + std::to_string(m_lives));
	sf::FloatRect textRect = m_livesText.getLocalBounds();
	m_livesText.setPosition(config->windowSize.x - textRect.width, 0.0f);
}

GameState::~GameState()
{
}

void GameState::handleInput(sf::RenderWindow* window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::KeyPressed && 
			(event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left))
			m_playersMovement->keyPressed(event.key.code);
		if (event.type == sf::Event::KeyReleased &&
			(event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left))
			m_playersMovement->keyReleased(event.key.code);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			m_player->shoot();
	}
}

void GameState::update(float deltaTime) 
{
	checkCollisions();
	m_playersMovement->update(deltaTime);
	if (m_playersMovement->shouldMove())
		m_player->move(m_playersMovement->getStep());
	m_playersBullets->update(deltaTime);
	m_player->update(deltaTime);
	m_enemiesBullets->update(deltaTime);
	m_enemies->update(deltaTime);
	m_pointsScorer->update(deltaTime);
}

void GameState::render(sf::RenderWindow* window)
{
	m_playersBullets->render(window);
	m_player->render(window);
	m_enemiesBullets->render(window);
	m_enemies->render(window);
	m_pointsScorer->render(window);
	window->draw(m_livesText);
}

void GameState::onEnter()
{
	auto* sharedContext = m_stateManager->getSharedContext();
	m_pointsScorer->resetScore();
	m_lives = sharedContext->config->lives;
	sharedContext->m_level = 0;
	start();
}

void GameState::onLeave()
{
	m_enemies->clear();
	m_playersBullets->clear();
	m_enemiesBullets->clear();
}

void GameState::checkCollisions()
{
	const auto bulletsSize = m_stateManager->getSharedContext()->config->bulletsSize;
	sf::RectangleShape bulletShape{bulletsSize};
	auto bulletsPositions = m_enemiesBullets->getBulletsPositions();
	for (auto bulletPos : bulletsPositions)
	{
		bulletShape.setPosition(bulletPos.x, bulletPos.y);
		if (isCollision(m_player->getPlayerShape(), bulletShape))
		{
			killMe();
			return;
		}
	}

	auto& enemies = m_enemies->getEnemies();
	for (auto& enemy : enemies)
	{
		if (isCollision(m_player->getPlayerShape(), enemy->getShape()))
		{
			killMe();
			return;
		}
	}

	bulletsPositions = m_playersBullets->getBulletsPositions();
	for (auto enemyIt = begin(enemies); enemyIt != end(enemies); ++enemyIt)
	{
		for (auto bulletPos : bulletsPositions)
		{
			bulletShape.setPosition(bulletPos.x, bulletPos.y);
			if (isCollision(bulletShape, (*enemyIt)->getShape()))
			{
				killTheEnemy(enemyIt, bulletPos);
				if (m_enemies->getEnemies().empty())
					nextLevel();
				return;
			}
		}
	}
}

bool GameState::isCollision(sf::RectangleShape first, sf::RectangleShape second) const
{
	return first.getGlobalBounds().intersects(second.getGlobalBounds());
}

void GameState::start()
{
	clearPlayer();
	m_enemies->clear();
	m_playersBullets->clear();
	m_enemiesBullets->clear();

	const float bulletsStep = getBulletsStep(); 
	m_enemiesBullets->setStep(bulletsStep);
	m_playersBullets->setStep(-1 * bulletsStep);

	setLivesText();
	m_enemies->add(getNumOfEnemiesRows(), getEnemiesSteps());
}

void GameState::clearPlayer()
{
	m_playersMovement->clear();
	m_player->start();
}

void GameState::killMe()
{
	--m_lives;
	if (m_lives == 0)
		m_stateManager->setNextState(StateManager::States::GameOver);
	else
	{
		clearPlayer();
		m_playersBullets->clear();
		m_enemiesBullets->clear();
		m_enemies->everybodyGoBack();
		setLivesText();
	}
}

void GameState::killTheEnemy(Enemies::EnemiesInfo::iterator enemyIt, sf::Vector2f bulletPos)
{
	m_pointsScorer->addPointsForKill((*enemyIt)->getAction());
	m_enemies->killed(enemyIt);
	m_playersBullets->remove(bulletPos);
}

void GameState::nextLevel()
{
	++m_stateManager->getSharedContext()->m_level;
	start();
}

void GameState::setLivesText()
{
	m_livesText.setString("Lives: " + std::to_string(m_lives));
}

// ========================== dummy logic ===============================

float GameState::getBulletsStep() const
{
	auto* shared = m_stateManager->getSharedContext();
	Config* config = shared->config;
	return config->bulletsStep + shared->m_level * config->nextLevelAcceleration;
}

unsigned GameState::getNumOfEnemiesRows() const
{
	auto* shared = m_stateManager->getSharedContext();
	Config* config = shared->config;
	return static_cast<unsigned>(config->numOfEnemiesRowsInFirstLevel + shared->m_level * config->numOfEnemiesRowsMultiplier);
}

float GameState::getEnemiesSteps() const
{
	auto* shared = m_stateManager->getSharedContext();
	Config* config = shared->config;
	return config->enemiesFirstLevelStep + shared->m_level * config->nextLevelAcceleration;
}