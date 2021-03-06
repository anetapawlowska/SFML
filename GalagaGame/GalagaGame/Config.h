#pragma once
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

struct Config
{
	void readConfig()
	{
		std::string delimiter = ":";
		std::ifstream cfgFile;
		cfgFile.open("config.txt");
		if (!cfgFile.is_open())
		{
			std::cerr << "! Failed loading config.txt." << std::endl;
			return;
		}
		std::string line;
		while (std::getline(cfgFile, line))
		{
			std::stringstream keystream(line);
			std::string name;
			float value;
			keystream >> name >> value;
			values[name] = value;
		}
		cfgFile.close();
		createConfig();
	}

	const unsigned lives = 3;

	const float startsStep{ 2.0f };
	const float playersMaxStep{ 16.0f };

	const sf::Vector2f buttonsSize{ 300, 50 };
	const sf::Vector2f playAgainButtonsPos{ 200, 300 };
	const sf::Vector2f endGameButtonsPos{ 200, 380 };
	const sf::Vector2f gameOverPointsPos{ 200, 180 };

	const sf::Vector2u windowSize{ 400, 480 };
	const sf::Vector2f playersSize{ 16.0f, 16.0f };
	const sf::Vector2f enemiesSize{ 16.0f, 16.0f };
	const sf::Vector2f bulletsSize{ 4.0f, 4.0f };
	
	float bulletsStep{ 10.0f };
	float playersStep{ 8.0f };
	float enemiesFirstLevelStep{ 6.0f };
	float nextLevelAcceleration{ 2.0f };

	const unsigned numOfEnemiesRowsInFirstLevel{ 3 };
	const float numOfEnemiesRowsMultiplier{ 0.5 };

	const sf::Color playersColor{ sf::Color::Green };
	const sf::Color shootersColor{ sf::Color::Red };
	const sf::Color nonShootersColor{ sf::Color::Blue };
	const sf::Color playersBulletsColor { sf::Color::Yellow };
	const sf::Color enemiesBulletsColor{ sf::Color::Yellow };
	const sf::Color buttonsColor{ sf::Color::Blue };

private:
	void createConfig()
	{
		bulletsStep = values["bulletsStep"];
		playersStep = values["playersStep"];
		enemiesFirstLevelStep = values["enemiesFirstLevelStep"];
		nextLevelAcceleration = values["enemiesNextLevelAcceleration"];
	}
	std::map<std::string, float> values;
};