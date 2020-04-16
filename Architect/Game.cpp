#include "Game.hpp"

#include <chrono>
using namespace std::chrono_literals;
constexpr std::chrono::nanoseconds timestep(16ms);

//keeps game loop running
static bool running = true;
//handler for quit event
void QuitHandler(Event &event) { running = false; }

Game::Game(const std::string &title, int width, int height)
{
	//initialize coordinator
	_coordinator.Init();

	//register quit event with coordinator
	_coordinator.AddEventListener(FUNCTION_LISTENER(Events::Window::QUIT, QuitHandler));

	//create window
	_window.create(title, width, height, &_coordinator);

	//initialize inputManager
	_inputManager.Init(&_coordinator);

	//register components with coordinator
	this->registerComponents();

	//register systems with coordinator
	this->registerSystems();

	this->Run();
}

void Game::registerComponents()
{
	_coordinator.RegisterComponent<Transform>();
	_coordinator.RegisterComponent<RigidBody>();
	_coordinator.RegisterComponent<Renderable>();
	_coordinator.RegisterComponent<Player>();
	_coordinator.RegisterComponent<PhysicsBody>();
	_coordinator.RegisterComponent<StaticComp>();
}

void Game::registerSystems()
{
	staticRenderSystem = _coordinator.RegisterSystem<StaticRenderSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<RigidBody>());
		signature.set(_coordinator.GetComponentType<Renderable>());
		signature.set(_coordinator.GetComponentType<StaticComp>());

		_coordinator.SetSystemSignature<StaticRenderSystem>(signature);
	}
	staticRenderSystem->Init(&_coordinator, _window.getRenderer());

	playerInputSystem = _coordinator.RegisterSystem<PlayerInputSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<PhysicsBody>());
		signature.set(_coordinator.GetComponentType<Player>());

		_coordinator.SetSystemSignature<PlayerInputSystem>(signature);
	}
	playerInputSystem->Init(&_coordinator);

	playerRenderSystem = _coordinator.RegisterSystem<PlayerRenderSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<RigidBody>());
		signature.set(_coordinator.GetComponentType<PhysicsBody>());
		signature.set(_coordinator.GetComponentType<Player>());
		signature.set(_coordinator.GetComponentType<Renderable>());

		_coordinator.SetSystemSignature<PlayerRenderSystem>(signature);
	}
	playerRenderSystem->Init(&_coordinator, _window.getRenderer());
}

void Game::Run()
{
	//create entities
	for (float i = 0; i < 2; i++)
	{
		for (float j = 0; j < 2; j++)
		{
			Entity entity = _coordinator.CreateEntity();
			_coordinator.AddComponent<Transform>(entity, { Math::Vector2f(i * 700, j * 500) });
			_coordinator.AddComponent<RigidBody>(entity, { Math::Vector2i(100, 100) });
			_coordinator.AddComponent<Renderable>(entity, { Math::Vector4i(0, 255, 0, 255) });
			_coordinator.AddComponent<StaticComp>(entity, {});
		}
	}

	Entity player = _coordinator.CreateEntity();
	_coordinator.AddComponent<Transform>(player, { Math::Vector2f(350.0f, 250.0f) });
	_coordinator.AddComponent<RigidBody>(player, { Math::Vector2i(100, 100) });
	_coordinator.AddComponent<PhysicsBody>(player, { Math::Vector2f() });
	_coordinator.AddComponent<Renderable>(player, { Math::Vector4i(200, 0, 200, 255) });
	_coordinator.AddComponent<Player>(player, {});

	//game loop
	using clock = std::chrono::high_resolution_clock;
	std::chrono::nanoseconds lag(0ns);
	auto prevTime = clock::now();
	auto currentTime = clock::now();
	auto elapsedTime = currentTime - prevTime;
	float interpolation = 0.0f;

	while (running)
	{
		currentTime = clock::now();
		elapsedTime = currentTime - prevTime;
		prevTime = currentTime;
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsedTime);

		//input/events
		_inputManager.Update();

		while (lag >= timestep)
		{
			lag -= timestep;

			//logic updates
			playerInputSystem->Update();
		}

		interpolation = std::chrono::duration<float, std::chrono::milliseconds::period>(lag / timestep).count();
		std::cout << interpolation << "\n";

		//render
		_window.clear(0, 0, 200, 255);

		staticRenderSystem->Update(interpolation);
		playerRenderSystem->Update(interpolation);

		_window.present();
	}

	_window.close();
}