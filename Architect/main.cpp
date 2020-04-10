#include <iostream>
#include <chrono>

#include "Core/ECS/Coordinator.hpp"
#include "Core/Components/Components.hpp"
#include "Core/Systems/AddingSystem.hpp"

Coordinator coordinator;

//clock stuff
auto start = std::chrono::steady_clock::now();

float getElapsedTimeInSeconds()
{
	auto end = std::chrono::steady_clock::now();

	return std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
}

int main()
{
	//initialize coordinator
	coordinator.Init();

	//register components with coordinator
	coordinator.RegisterComponent<OneComponent>();
	coordinator.RegisterComponent<SumComponent>();

	//register systems with coordinator
	auto addingSystem = coordinator.RegisterSystem<AddingSystem>();
	{
		//create system signature

		//this makes sure only the entities with these 
		//components get passed through the system
		
		Signature signature;

		signature.set(coordinator.GetComponentType<OneComponent>());
		signature.set(coordinator.GetComponentType<SumComponent>());

		coordinator.SetSystemSignature<AddingSystem>(signature);
	}
	//initialize the system
	addingSystem->Init();

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
	float currentTime = getElapsedTimeInSeconds();
	float accumulator = 0.0f;

	bool game_is_running = true;

	while (game_is_running)
	{
		newTime = getElapsedTimeInSeconds();
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
	}

	return 0;
}