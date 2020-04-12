#include "PlayerInputSystem.hpp"

#include "../Components/PositionComponent.hpp"
#include "../Components/PlayerComponent.hpp"

#include "../Input/InputButtons.hpp"

void PlayerInputSystem::Init(Coordinator *coordinator)
{
	_coordinator = coordinator;

	if (_coordinator != nullptr)
	{
		_coordinator->AddEventListener(METHOD_LISTENER(Events::Window::INPUT, PlayerInputSystem::InputListener));
	}
}

void PlayerInputSystem::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
		//auto& playerComp = _coordinator->GetComponent<PlayerComponent>(entity);
		auto& posComp = _coordinator->GetComponent<PositionComponent>(entity);

		if (_buttons.test(static_cast<std::size_t>(InputButtons::A))) posComp.x -= 10;
		else if (_buttons.test(static_cast<std::size_t>(InputButtons::D))) posComp.x += 10;

		if (_buttons.test(static_cast<std::size_t>(InputButtons::W))) posComp.y -= 10;
		else if (_buttons.test(static_cast<std::size_t>(InputButtons::S))) posComp.y += 10;
	}
}

void PlayerInputSystem::InputListener(Event &event)
{
	_buttons = event.GetParam<std::bitset<8>>(Events::Window::Input::INPUT);
}