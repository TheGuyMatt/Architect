#include "PlayerInputSystem.hpp"

#include "../Components/PositionComponent.hpp"
#include "../Components/PlayerComponent.hpp"

void PlayerInputSystem::Init(Coordinator *coordinator)
{
	_coordinator = coordinator;
}

void PlayerInputSystem::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
		//auto& playerComp = _coordinator->GetComponent<PlayerComponent>(entity);
		auto& posComp = _coordinator->GetComponent<PositionComponent>(entity);

		SDL_Event evnt;
		if (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym)
				{
				case SDLK_LEFT:
					posComp.x -= 10;
					break;
				case SDLK_RIGHT:
					posComp.x += 10;
					break;
				case SDLK_UP:
					posComp.y -= 10;
					break;
				case SDLK_DOWN:
					posComp.y += 10;
					break;

				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	}
}