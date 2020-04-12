#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <chrono>

//window
#include "Core/Window.hpp"

//ECS
#include "Core/Coordinator.hpp"
//Systems
#include "Core/Systems/RenderRectSystem.hpp"
#include "Core/Systems/PlayerInputSystem.hpp"
//Components
#include "Core/Components/PositionComponent.hpp"
#include "Core/Components/SizeComponent.hpp"
#include "Core/Components/ColorComponent.hpp"
#include "Core/Components/PlayerComponent.hpp"

//typedef std::shared_ptr<Window> WindowRef;
//WindowRef _window = std::make_shared<Window>();

class Game
{
public:
	Game(const std::string &title, int width, int height);

private:
	//window
	Window _window;

	//coordinator
	Coordinator _coordinator;

	//systems
	//std::shared_ptr<SYSTEM> system;
	std::shared_ptr<RenderRectSystem> renderRectsystem;
	std::shared_ptr<PlayerInputSystem> playerInputSystem;

	//clock stuff
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	float getElapsedClockTime();

	void Run();
};

#endif