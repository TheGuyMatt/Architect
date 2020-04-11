#include <iostream>
#include "Core/Game.hpp"

//Include SDL
#define SDL_MAIN_HANDLED
#include <SDL.h>

int main()
{
	//Get SDL Ready
	SDL_SetMainReady();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "SDL Failed to initialize\n";
	}
	else std::cout << "SDL initialized\n";

	//initialize game
	//Game::Game();

	return 0;
}