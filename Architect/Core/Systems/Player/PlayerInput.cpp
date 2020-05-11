#include "PlayerInput.hpp"

#include "../../Components/Player.hpp"
#include "../../Components/PhysicsBody.hpp"

#include "../../Input/InputButtons.hpp"

void PlayerInput::Init(Coordinator *coordinator)
{
	_coordinator = coordinator;

	if (_coordinator != nullptr)
	{
		_coordinator->AddEventListener(METHOD_LISTENER(Events::Window::INPUT, PlayerInput::InputListener));
	}
}

void PlayerInput::Update()
{
	for (auto const& entity : mEntities)
	{
		//auto& playerComp = _coordinator->GetComponent<Player>(entity);
		auto& physicsBody = _coordinator->GetComponent<PhysicsBody>(entity);

		float speed = 10;

		if (_buttons.test(static_cast<std::size_t>(InputButtons::A))) physicsBody.velocity.x = -speed;
		else if (_buttons.test(static_cast<std::size_t>(InputButtons::D))) physicsBody.velocity.x = speed;
		else physicsBody.velocity.x = 0.0f;

		if (_buttons.test(static_cast<std::size_t>(InputButtons::W))) physicsBody.velocity.y = -speed;
		else if (_buttons.test(static_cast<std::size_t>(InputButtons::S))) physicsBody.velocity.y = speed;
		else physicsBody.velocity.y = 0.0f;
	}
}

void PlayerInput::InputListener(Event &event)
{
	_buttons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}