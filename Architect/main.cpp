#include <iostream>
#include "Game.hpp"

//Include SDL
#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "Core/Window.hpp"

int main()
{
	//Get SDL Ready
	SDL_SetMainReady();

	//window
	Window window("Architect", 800, 600);

	while (!window.isClosed())
	{
		window.pollEvents();
	}

	//initialize game
	//Game::Game();

	return 0;
}