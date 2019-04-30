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
	sf::Vector2f enemiesBulletsSize{ 4.0f, 4.0f };
	sf::Vector2f playersBulletsSize{ 4.0f, 4.0f };
	float playersBulletStep { -10.0f };
	float enemysBulletStep{ 10.0f };
	float playersStep{ 8.0f };
	float enemiesFirstLevelStep{ 4.0f };

	sf::Color playersColor{ sf::Color::Red };
	sf::Color enemysColor { sf::Color::Blue };
	sf::Color playersBulletsColor { sf::Color::White };
	sf::Color enemiesBulletsColor{ sf::Color::White };
private:
	void createConfig()
	{
		const auto windowSizeX = static_cast<unsigned>(values["windowSizeX"]);
		const auto windowSizeY = static_cast<unsigned>(values["windowSizeY"]);
		windowSize = { windowSizeX, windowSizeY };

		const auto playersSizeX = values["playersSizeX"];
		const auto playersSizeY = values["playersSizeY"];
		playersSize = { playersSizeX, playersSizeY };

		const auto enemiesSizeX = values["enemiesSizeX"];
		const auto enemiesSizeY = values["enemiesSizeY"];
		enemiesSize = { enemiesSizeX, enemiesSizeY };

		const auto enemiesBulletsSizeX = values["enemiesBulletsSizeX"];
		const auto enemiesBulletsSizeY = values["enemiesBulletsSizeY"];
		enemiesBulletsSize = { enemiesBulletsSizeX, enemiesBulletsSizeY };

		const auto playersBulletsSizeX = values["playersBulletsSizeX"];
		const auto playersBulletsSizeY = values["playersBulletsSizeY"];
		playersBulletsSize = { playersBulletsSizeX, playersBulletsSizeY };

		playersBulletStep = values["playersBulletStep"];
		enemysBulletStep = values["enemysBulletStep"];
		playersStep = values["playersStep"];
		enemiesFirstLevelStep = values["enemiesFirstLevelStep"];
	}
	std::map<std::string, float> values;
};