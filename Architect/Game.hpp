#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <chrono>

//window
#include "Core/Window.hpp"

//ECS
#include "Core/Coordinator.hpp"
//Systems
#include "Core/Systems/StaticRenderSystem.hpp"
#include "Core/Systems/PlayerInputSystem.hpp"
#include "Core/Systems/PlayerRenderSystem.hpp"
#include "Core/Systems/PlayerMoveSystem.hpp"
//Components
#include "Core/Components/Transform.hpp"
#include "Core/Components/RidgidBody.hpp"
#include "Core/Components/Renderable.hpp"
#include "Core/Components/Player.hpp"
#include "Core/Components/PhysicsBody.hpp"
#include "Core/Components/StaticComp.hpp"

//Events
#include "Core/Events/EventDependencies.hpp"

//Input
#include "Core/Input/InputManager.hpp"

//Math 
#include "Core/Math/Vector2.hpp"
#include "Core/Math/Vector3.hpp"
#include "Core/Math/Vector4.hpp"

//typedef std::shared_ptr<Window> WindowRef;
//WindowRef _window = std::make_shared<Window>();

class Game
{
public:
	Game(const std::string &title, int width, int height);

private:
	Window _window;
	Coordinator _coordinator;
	InputManager _inputManager;

	//systems
	//std::shared_ptr<SYSTEM> system;
	std::shared_ptr<StaticRenderSystem> staticRenderSystem;
	std::shared_ptr<PlayerInputSystem> playerInputSystem;
	std::shared_ptr<PlayerRenderSystem> playerRenderSystem;
	std::shared_ptr<PlayerMoveSystem> playerMoveSystem;

	void registerComponents();
	void registerSystems();

	void HandleInput();
	void Update();
	void Render();

	void Run();
};

#endif