#include "AddingSystem.hpp"

#include "../Components/Components.hpp"
#include "../ECS/Coordinator.hpp"

extern Coordinator coordinator;

void AddingSystem::Init()
{
}

void AddingSystem::Update(float dt)
{
	system("CLS");

	for (auto const& entity : mEntities)
	{
		auto& oneComponent = coordinator.GetComponent<OneComponent>(entity);
		auto& sumComponent = coordinator.GetComponent<SumComponent>(entity);

		sumComponent.sum = oneComponent.num + sumComponent.sum;
		std::cout << sumComponent.sum << std::endl;
	}
}