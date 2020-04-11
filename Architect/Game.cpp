#include "Game.hpp"

float Game::getElapsedClockTime()
{
	auto end = std::chrono::steady_clock::now();

	return (float)std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
}

Game::Game(const std::string &title, int width, int height)
{
	_window->create("Architect", width, height);

	//initialize coordinator
	_coordinator.Init();

	//register components with coordinator
	//coordinator.RegisterComponent<COMPONENT>();
	_coordinator.RegisterComponent<PositionComponent>();
	_coordinator.RegisterComponent<SizeComponent>();
	_coordinator.RegisterComponent<ColorComponent>();

	/* register systems
	system = coordinator.RegisterSystem<SYSTEM>();
	{
		//a systems signature are the components that 
		//an entity has to have in order to be passed
		//through the system

		Signature signature;

		signature.set(coordinator.GetComponentType<COMPONENT>());

		coordinator.SetSystemSignature<SYSTEM>(signature);
	}
	//each system needs a reference to coordinator to work
	addingSystem->Init(&coordinator);
	*/

	renderRectsystem = _coordinator.RegisterSystem<RenderRectSystem>();
	{
		Signature signature;

		signature.set(_coordinator.GetComponentType<PositionComponent>());
		signature.set(_coordinator.GetComponentType<SizeComponent>());
		signature.set(_coordinator.GetComponentType<ColorComponent>());

		_coordinator.SetSystemSignature<RenderRectSystem>(signature);
	}
	renderRectsystem->Init(&_coordinator, _window->getRenderer());

	this->Run();
}

void Game::Run()
{
	/* create an entity and add components to it
	Entity entity = coordinator.CreateEntity();
	coordinator.AddComponent<COMPONENT>(entity, { int(i) });
	*/

	Entity entity = _coordinator.CreateEntity();
	_coordinator.AddComponent<PositionComponent>(entity, { int(100), int(100)});
	_coordinator.AddComponent<SizeComponent>(entity, { int(120), int(120) });
	_coordinator.AddComponent<ColorComponent>(entity, { int(200), int(0), int(200), int(255) });

	//game loop
	float dt = 1.0f / 60.0f;
	float newTime, frameTime, interpolation;
	float currentTime = this->getElapsedClockTime();
	float accumulator = 0.0f;

	while (!_window->isClosed())
	{
		newTime = this->getElapsedClockTime();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator > dt)
		{
			_window->pollEvents();

			//update systems here
			//system->Update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;

		//rendering systems goes here with interpolation
		_window->clear(0, 0, 0, 255);

		renderRectsystem->Update(interpolation);

		_window->present();
	}
}