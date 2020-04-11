#include "Game.hpp"

float Game::getElapsedClockTime()
{
	auto end = std::chrono::steady_clock::now();

	return (float)std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
}

Game::Game()
{
	//initialize coordinator
	coordinator.Init();

	//register components with coordinator
	coordinator.RegisterComponent<OneComponent>();
	coordinator.RegisterComponent<SumComponent>();

	//register systems
	addingSystem = coordinator.RegisterSystem<AddingSystem>();
	{
		//create system signature

		//this makes sure only the entities with these 
		//components get passed through the system

		Signature signature;

		signature.set(coordinator.GetComponentType<OneComponent>());
		signature.set(coordinator.GetComponentType<SumComponent>());

		coordinator.SetSystemSignature<AddingSystem>(signature);
	}
	//each system needs a reference to coordinator to work
	addingSystem->Init(&coordinator);

	this->Run();
}

void Game::Run()
{
	//create an entity and add components to it
	for (unsigned int i = 1; i <= 3; i++)
	{
		Entity entity = coordinator.CreateEntity();
		coordinator.AddComponent<OneComponent>(entity, { int(i) });
		coordinator.AddComponent<SumComponent>(entity, { int(0) });
	}

	//game loop
	float dt = 1.0f / 60.0f;
	float newTime, frameTime, interpolation;
	float currentTime = this->getElapsedClockTime();
	float accumulator = 0.0f;

	bool game_is_running = true;

	while (game_is_running)
	{
		newTime = this->getElapsedClockTime();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator > dt)
		{
			//update systems here
			addingSystem->Update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;

		//rendering systems goes here with interpolation

		//tempory thing to end the program after a given amount of seconds
		if (this->getElapsedClockTime() >= 3.0f) game_is_running = false;
	}
}