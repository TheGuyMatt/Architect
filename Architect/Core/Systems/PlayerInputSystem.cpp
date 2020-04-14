#include "PlayerInputSystem.hpp"

#include "../Components/Transform.hpp"
#include "../Components/Player.hpp"

#include "../Input/InputButtons.hpp"

void PlayerInputSystem::Init(Coordinator *coordinator)
{
	_coordinator = coordinator;

	if (_coordinator != nullptr)
	{
		_coordinator->AddEventListener(METHOD_LISTENER(Events::Window::INPUT, PlayerInputSystem::InputListener));
	}
}

void PlayerInputSystem::Update()
{
	for (auto const& entity : mEntities)
	{
		//auto& playerComp = _coordinator->GetComponent<Player>(entity);
		auto& transform = _coordinator->GetComponent<Transform>(entity);

		transform.previous_pos = transform.position;

		float speed = 30;
		if (_buttons.test(static_cast<std::size_t>(InputButtons::A))) transform.position.x -= speed;
		else if (_buttons.test(static_cast<std::size_t>(InputButtons::D))) transform.position.x += speed;

		if (_buttons.test(static_cast<std::size_t>(InputButtons::W))) transform.position.y -= speed;
		else if (_buttons.test(static_cast<std::size_t>(InputButtons::S))) transform.position.y += speed;
	}
}

void PlayerInputSystem::InputListener(Event &event)
{
	_buttons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}