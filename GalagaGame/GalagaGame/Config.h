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
	}

	sf::Vector2u windowSize{ 400, 480 };
	sf::Vector2f playersSize{ 16.0f, 16.0f };
	sf::Vector2f enemiesSize{ 16.0f, 16.0f };
	sf::Vector2f bulletsSize{ 4.0f, 4.0f };
	
	float bulletsStep{ 10.0f };
	float playersStep{ 8.0f };
	float enemiesFirstLevelStep{ 6.0f };
	float nextLevelAcceleration{ 2.0f };

	unsigned numOfEnemiesRowsInFirstLevel{ 3 };
	float numOfEnemiesRowsMultiplier{ 0.5 };

	sf::Color playersColor{ sf::Color::Green };
	sf::Color shootersColor{ sf::Color::Red };
	sf::Color nonShootersColor{ sf::Color::Blue };
	sf::Color playersBulletsColor { sf::Color::Yellow };
	sf::Color enemiesBulletsColor{ sf::Color::Yellow };
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