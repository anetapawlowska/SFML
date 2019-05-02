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

GameState::GameState(StateManager* stateManager) : m_stateManager{ stateManager }
{
	Config* config = m_stateManager->getSharedContext()->config;

	m_playersBullets = std::make_unique<Bullets>(config->windowSize, config->bulletsSize, config->playersBulletsColor);
	m_player = std::make_unique<Player>(m_playersBullets.get(), config->windowSize, config->playersSize, config->playersColor);
	m_enemiesBullets = std::make_unique<Bullets>(config->windowSize, config->bulletsSize, config->enemiesBulletsColor);
	m_enemies = std::make_unique<Enemies>(m_enemiesBullets.get(), config->windowSize, config->enemiesSize, config->shootersColor, config->nonShootersColor);

	m_font.loadFromFile("arial.ttf");
	m_pointsText.setFont(m_font);
	m_pointsText.setCharacterSize(15);
	m_pointsText.setFillColor(sf::Color::White);

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
			keyPressed(event.key.code);
		if (event.type == sf::Event::KeyReleased &&
			(event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left))
			keyReleased(event.key.code);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			m_player->shoot();
	}
}

void GameState::update(float deltaTime) 
{
	checkCollisions();
	checkPlayersMove();
	m_playersBullets->update(deltaTime);
	m_player->update(deltaTime);
	m_enemiesBullets->update(deltaTime);
	m_enemies->update(deltaTime);
}

void GameState::render(sf::RenderWindow* window)
{
	m_playersBullets->render(window);
	m_player->render(window);
	m_enemiesBullets->render(window);
	m_enemies->render(window);
	window->draw(m_pointsText);
	window->draw(m_livesText);
}

void GameState::onEnter()
{
	auto* sharedContext = m_stateManager->getSharedContext();
	sharedContext->points = 0;
	setScoreText();
	m_lives = sharedContext->config->lives;
	sharedContext->m_level = 0;
	start();
}

void GameState::onLeave()
{
	clear();
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
	clear();
	m_livesText.setString("Lives: " + std::to_string(m_lives));

	const float bulletsStep = getBulletsStep(); 
	m_enemiesBullets->setStep(bulletsStep);
	m_playersBullets->setStep(-1 * bulletsStep);

	m_enemies->add(getNumOfEnemiesRows(), getEnemiesSteps());
}

void GameState::clearPlayer()
{
	m_keyPressedCounter = 0;
	m_isKeyPressed = false;
	m_playersDirection = PlayersDirection::none;
	m_player->start();
}

void GameState::clear()
{
	m_enemies->clear();
	m_playersBullets->clear();
	m_enemiesBullets->clear();
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
	}
}

void GameState::killTheEnemy(Enemies::EnemiesInfo::iterator enemyIt, sf::Vector2f bulletPos)
{
	addPointsForKill((*enemyIt)->getAction());
	m_enemies->killed(enemyIt);
	m_playersBullets->remove(bulletPos);
}

void GameState::nextLevel()
{
	++m_stateManager->getSharedContext()->m_level;
	start();
}

void GameState::keyPressed(sf::Keyboard::Key key)
{
	if (key != sf::Keyboard::Key::Right && key != sf::Keyboard::Key::Left)
		return;

	m_isKeyPressed = true;
	m_playersDirection = key == sf::Keyboard::Key::Right ? PlayersDirection::right : PlayersDirection::left;
	m_keyPressedCounter = 0;
}

void GameState::keyReleased(sf::Keyboard::Key key)
{
	if ((key == sf::Keyboard::Key::Right && m_playersDirection == PlayersDirection::right) ||
		(key == sf::Keyboard::Key::Left && m_playersDirection == PlayersDirection::left))
		m_isKeyPressed = false;
}

void GameState::checkPlayersMove()
{
	if (m_playersDirection == PlayersDirection::none)
		return;

	const auto maxPlayersStep = m_stateManager->getSharedContext()->config->playersMaxStep;

	if (m_isKeyPressed && getPlayersStep() < maxPlayersStep )
		++m_keyPressedCounter;
	else if (m_keyPressedCounter > 0)
		--m_keyPressedCounter;

	if (m_keyPressedCounter == 0)
	{
		m_playersDirection = PlayersDirection::none;
		return;
	}

	float step = getPlayersStep();
	if (m_playersDirection == PlayersDirection::left)
		step *= -1;
	m_player->move(step);
}

void GameState::addPointsForKill(Enemy::Action action)
{
	const unsigned points = getPointsForKill(action);
	const auto config = m_stateManager->getSharedContext();
	config->points += points;
	setScoreText();
}

void GameState::setScoreText()
{
	const auto config = m_stateManager->getSharedContext();
	m_pointsText.setString("Score: " + std::to_string(config->points));
}

// ========================== dummy logic ===============================

float GameState::getPlayersStep() const
{
	auto* config = m_stateManager->getSharedContext()->config;
	const float multiplier = 0.5f;
	float step = config->playersStep;
	step += m_keyPressedCounter * multiplier;
	return std::min(step, config->playersMaxStep);
}

unsigned GameState::getPointsForKill(Enemy::Action action) const
{
	const unsigned pointsForKill = 50;
	const unsigned pointsForAttacker = 75;
	return action == Enemy::Action::attack ? pointsForAttacker : pointsForKill;
}

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