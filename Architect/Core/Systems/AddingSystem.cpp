#include "AddingSystem.hpp"

#include "../Components/Components.hpp"

void AddingSystem::Init(Coordinator* coordinator)
{
	_coordinator = coordinator;
}

void AddingSystem::Update(float dt)
{
	system("CLS");

	for (auto const& entity : mEntities)
	{
		auto& oneComponent = _coordinator->GetComponent<OneComponent>(entity);
		auto& sumComponent = _coordinator->GetComponent<SumComponent>(entity);

		sumComponent.sum = oneComponent.num + sumComponent.sum;
		std::cout << sumComponent.sum << std::endl;
	}
}