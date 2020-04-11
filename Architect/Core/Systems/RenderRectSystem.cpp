#include "RenderRectSystem.hpp"

#include "../Components/PositionComponent.hpp"
#include "../Components/SizeComponent.hpp"
#include "../Components/ColorComponent.hpp"

void RenderRectSystem::Init(Coordinator *coordinator, SDL_Renderer *renderer)
{
	_coordinator = coordinator;
	_renderer = renderer;
}

void RenderRectSystem::Update(float interpolation)
{
	for (auto const& entity : mEntities)
	{
		auto& posComp = _coordinator->GetComponent<PositionComponent>(entity);
		auto& sizeComp = _coordinator->GetComponent<SizeComponent>(entity);
		auto& colorComp = _coordinator->GetComponent<ColorComponent>(entity);

		SDL_Rect rect;
		rect.x = posComp.x;
		rect.y = posComp.y;
		rect.w = sizeComp.width;
		rect.h = sizeComp.height;
		SDL_SetRenderDrawColor(_renderer, colorComp.red, colorComp.green, colorComp.blue, colorComp.alpha);
		SDL_RenderFillRect(_renderer, &rect);
	}
}