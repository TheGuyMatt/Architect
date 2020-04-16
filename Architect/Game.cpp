#include "Game.hpp"
#include <Windows.h>

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
}

void Game::registerSystems()
{
	renderRectsystem = _coordinator.RegisterSystem<RenderRectSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<RigidBody>());
		signature.set(_coordinator.GetComponentType<Renderable>());

		_coordinator.SetSystemSignature<RenderRectSystem>(signature);
	}
	renderRectsystem->Init(&_coordinator, _window.getRenderer());

	playerInputSystem = _coordinator.RegisterSystem<PlayerInputSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<Player>());

		_coordinator.SetSystemSignature<PlayerInputSystem>(signature);
	}
	playerInputSystem->Init(&_coordinator);
}

void Game::Run()
{
	//create entities
	Entity player = _coordinator.CreateEntity();
	_coordinator.AddComponent<Transform>(player, { Math::Vector2f(350.0f, 250.0f), Math::Vector2f(350.0f, 250.0f) });
	_coordinator.AddComponent<RigidBody>(player, { Math::Vector2i(100, 100) });
	_coordinator.AddComponent<Renderable>(player, { Math::Vector4i(200, 0, 200, 255) });
	_coordinator.AddComponent<Player>(player, {});

	for (float i = 0; i < 2; i++)
	{
		for (float j = 0; j < 2; j++)
		{
			Entity entity = _coordinator.CreateEntity();
			_coordinator.AddComponent<Transform>(entity, { Math::Vector2f(i * 700, j * 500), Math::Vector2f(i * 700, j * 500) });
			_coordinator.AddComponent<RigidBody>(entity, { Math::Vector2i(100, 100) });
			_coordinator.AddComponent<Renderable>(entity, { Math::Vector4i(0, 255, 0, 255) });
		}
	}

	//game loop
	const int TICKS_PER_SECOND = 30;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;

	DWORD next_game_tick = GetTickCount();
	int loops;
	float interpolation;

	while (running)
	{
		loops = 0;

		while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP)
		{
			//input/events
			_inputManager.Update();
			//logic updates
			playerInputSystem->Update();

			next_game_tick += SKIP_TICKS;
			loops++;
		}

		interpolation = float(GetTickCount() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);

		//render
		_window.clear(0, 0, 200, 255);

		renderRectsystem->Update(interpolation);

		_window.present();
	}

	_window.close();
}