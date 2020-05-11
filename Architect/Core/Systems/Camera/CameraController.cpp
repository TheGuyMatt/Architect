#include "CameraController.hpp"

//also checks if entity has player component
#include "../../Components/Transform.hpp"
#include "../../Components/RidgidBody.hpp"

void CameraController::Init(Coordinator* coordinator, Camera* camera)
{
	_coordinator = coordinator;
	_worldCamera = camera;
}

void CameraController::Update()
{
	for (auto const& entity : mEntities)
	{
		auto& transform = _coordinator->GetComponent<Transform>(entity);
		auto& rigidBody = _coordinator->GetComponent<RigidBody>(entity);

		_worldCamera->position.x = transform.position.x - 400.0f + rigidBody.size.x / 2;
		_worldCamera->position.y = transform.position.y - 300.0f + rigidBody.size.y / 2;
	}
}