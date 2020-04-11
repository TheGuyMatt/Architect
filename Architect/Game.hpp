#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <chrono>

#include "Core/ECS/Coordinator.hpp"
#include "Core/Components/Components.hpp"
#include "Core/Systems/AddingSystem.hpp"

class Game
{
public:
	Game();

private:
	//create the global coordinator
	Coordinator coordinator;

	//systems
	std::shared_ptr<AddingSystem> addingSystem;

	//clock stuff
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	float getElapsedClockTime();

	void Run();
};

#endif