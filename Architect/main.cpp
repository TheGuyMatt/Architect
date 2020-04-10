#include "Core/ECS/Coordinator.hpp"
#include "Core/Components/Components.hpp"
#include "Core/Systems/AddingSystem.hpp"

Coordinator coordinator;

int main()
{
	//initialize coordinator
	coordinator.Init();

	//register components with coordinator
	coordinator.RegisterComponent<OneComponent>();
	coordinator.RegisterComponent<TwoComponent>();
	coordinator.RegisterComponent<SumComponent>();

	//register systems with coordinator
	auto addingSystem = coordinator.RegisterSystem<AddingSystem>();
	{
		//create system signature

		//this makes sure only the entities with these 
		//components get passed through the system
		
		Signature signature;

		signature.set(coordinator.GetComponentType<OneComponent>());
		signature.set(coordinator.GetComponentType<TwoComponent>());
		signature.set(coordinator.GetComponentType<SumComponent>());

		coordinator.SetSystemSignature<AddingSystem>(signature);
	}
	//initialize the system
	addingSystem->Init();

	//create an entity and add components to it
	for (unsigned int i = 1; i <= 5; i++)
	{
		Entity entity = coordinator.CreateEntity();
		coordinator.AddComponent<OneComponent>(entity, { int(i) });
		coordinator.AddComponent<TwoComponent>(entity, { int(i) });
		coordinator.AddComponent<SumComponent>(entity, { int(0) });
	}

	float dt = 0.0f;
	addingSystem->Update(dt);

	system("PAUSE");

	return 0;
}