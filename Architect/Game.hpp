#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <chrono>

//window
#include "Core/Window.hpp"

//ECS
#include "Core/ECS/Coordinator.hpp"
#include "Core/Systems/RenderRectSystem.hpp"
#include "Core/Components/PositionComponent.hpp"
#include "Core/Components/SizeComponent.hpp"
#include "Core/Components/ColorComponent.hpp"

typedef std::shared_ptr<Window> WindowRef;

class Game
{
public:
	Game(const std::string &title, int width, int height);

private:
	//window
	WindowRef _window = std::make_shared<Window>();

	//coordinator
	Coordinator _coordinator;

	//systems
	//std::shared_ptr<SYSTEM> system;
	std::shared_ptr<RenderRectSystem> renderRectsystem;

	//clock stuff
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	float getElapsedClockTime();

	void Run();
};

#endif