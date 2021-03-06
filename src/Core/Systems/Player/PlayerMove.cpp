#include "PlayerMove.hpp"

#include "../../Components/Transform.hpp"
#include "../../Components/PhysicsBody.hpp"

void PlayerMove::Init(Coordinator* coordinator)
{
	_coordinator = coordinator;
}

void PlayerMove::Update()
{
	for (auto const& entity : mEntities)
	{
		auto& transform = _coordinator->GetComponent<Transform>(entity);
		auto& physicsBody = _coordinator->GetComponent<PhysicsBody>(entity);

		transform.position += physicsBody.velocity;
	}
}