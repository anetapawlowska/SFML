#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Window.h"

void main(int argc, char** argv[])
{
	Game game;
	while (!game.getWindow()->isDone())
	{
		game.handleInput();
		game.update();
		game.render();
		game.lateUpdate();
	}

}