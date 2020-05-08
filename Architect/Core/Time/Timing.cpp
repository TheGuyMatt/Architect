#include "Timing.hpp"

#include <SDL.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
static double freq;
static bool timerInitialized = false;

//TODO: Support other operating systems
//currently only compiles with windows

double Time::getTime()
{
	if (!timerInitialized)
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			std::cerr << "QueryPerformanceFrequency failed in timer initialization\n";

		freq = double(li.QuadPart);
		timerInitialized = true;
	}

	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cerr << "QueryPerformanceFrequency failed in getTime()\n";

	return double(li.QuadPart) / freq;
}

void Time::sleep(int milliseconds)
{
	SDL_Delay(milliseconds);
}