#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Engine.h"

int main()
{
	Engine game;
	while (game.getWindow()->isOpen())
	{
		game.handleInput();
		game.update();
		game.render();
		game.restartClock();
	}
}