#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <chrono>

//window
#include "Core/Window.hpp"

//ECS
#include "Core/Coordinator.hpp"
//Systems
#include "Core/Systems/StaticRender.hpp"
#include "Core/Systems/Player/PlayerInput.hpp"
#include "Core/Systems/Player/PlayerRender.hpp"
#include "Core/Systems/Player/PlayerMove.hpp"
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

//Camera
#include "Core/Systems/Camera/Camera.hpp"
#include "Core/Systems/Camera/CameraController.hpp"

//Rendering
#include "Core/Rendering/ResourceManager.hpp"

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

	std::shared_ptr<CameraController> cameraController;
	Camera worldCamera;

	//systems
	//std::shared_ptr<SYSTEM> system;
	std::shared_ptr<StaticRender> staticRender;
	std::shared_ptr<PlayerInput> playerInput;
	std::shared_ptr<PlayerRender> playerRender;
	std::shared_ptr<PlayerMove> playerMove;

	void registerComponents();
	void registerSystems();

	void HandleInput();
	void Update();
	void Render();

	void Run();
};

#endif
