#include <iostream>
#include "Game.hpp"
#include "Core/Util/Log.hpp"

#define SDL_MAIN_HANDLED
#include <SDL.h>

int main(int argc, char *argv[])
{
	//Get SDL Ready
	SDL_SetMainReady();

	//initialize game
	Game("Architect", 800, 600);

	return 0;
}