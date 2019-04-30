#pragma once
#include <SFML\Graphics.hpp>
#include "Config.h"

struct SharedContext
{
	SharedContext(Config* config) : config{ config } {}
	
	Config* config;
	long long unsigned points;
};
