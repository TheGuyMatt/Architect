#include "Game.hpp"

#include <chrono>
using namespace std::chrono_literals;
//fixed time step of 1 / (60 fps)
constexpr std::chrono::nanoseconds timestep(16ms);
const float dt = 1.0f / 60.0f;

Game::Game(const std::string &title, int width, int height)
{
	//create window
	_window.create(title, width, height);

	//initialize coordinator
	_coordinator.Init();

	//initialize inputManager
	_inputManager.Init(&_coordinator, &_window);

	//register components with coordinator
	_coordinator.RegisterComponent<PositionComponent>();
	_coordinator.RegisterComponent<SizeComponent>();
	_coordinator.RegisterComponent<ColorComponent>();
	_coordinator.RegisterComponent<PlayerComponent>();

	//register systems
	renderRectsystem = _coordinator.RegisterSystem<RenderRectSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<PositionComponent>());
		signature.set(_coordinator.GetComponentType<SizeComponent>());
		signature.set(_coordinator.GetComponentType<ColorComponent>());

		_coordinator.SetSystemSignature<RenderRectSystem>(signature);
	}
	renderRectsystem->Init(&_coordinator, _window.getRenderer());

	playerInputSystem = _coordinator.RegisterSystem<PlayerInputSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<PositionComponent>());
		signature.set(_coordinator.GetComponentType<PlayerComponent>());

		_coordinator.SetSystemSignature<PlayerInputSystem>(signature);
	}
	playerInputSystem->Init(&_coordinator);

	this->Run();
}

void Game::Run()
{
	//create an entity and add components to it

	Entity entity = _coordinator.CreateEntity();
	_coordinator.AddComponent<PositionComponent>(entity, { int(100), int(100)});
	_coordinator.AddComponent<SizeComponent>(entity, { int(120), int(120) });
	_coordinator.AddComponent<ColorComponent>(entity, { int(200), int(0), int(200), int(255) });
	_coordinator.AddComponent<PlayerComponent>(entity, {});

	//game loop
	using clock = std::chrono::high_resolution_clock;
	std::chrono::nanoseconds lag(0ms);
	auto previousTime = clock::now();

	while (!_window.isClosed())
	{
		auto currentTime = clock::now();
		auto elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsedTime);

		//input/events
		_inputManager.Update();

		while (lag >= timestep)
		{
			//logic updates
			playerInputSystem->Update(dt);

			lag -= timestep;
		}

		float interpolation = static_cast<float>(lag / timestep);

		//render with interpolation
		_window.clear(0, 0, 0, 255);

		renderRectsystem->Update(interpolation);

		_window.present();
	}
}