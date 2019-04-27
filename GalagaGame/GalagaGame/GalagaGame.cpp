#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Window.h"

int main()
{
	Engine game;
	while (!game.getWindow()->isDone())
	{
		game.handleInput();
		game.update();
		game.render();
	}
}