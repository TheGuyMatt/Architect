#include "RenderRectSystem.hpp"

#include "../Components/Transform.hpp"
#include "../Components/RidgidBody.hpp"
#include "../Components/Renderable.hpp"

void RenderRectSystem::Init(Coordinator *coordinator, SDL_Renderer *renderer)
{
	_coordinator = coordinator;
	_renderer = renderer;
}

void RenderRectSystem::Update(float interpolation)
{
	for (auto const& entity : mEntities)
	{
		auto& transform = _coordinator->GetComponent<Transform>(entity);
		auto& ridgidBody = _coordinator->GetComponent<RigidBody>(entity);
		auto& renderable = _coordinator->GetComponent<Renderable>(entity);

		Math::Vector2f currPos = transform.position;
		Math::Vector2f prevPos = transform.previous_pos;
		Math::Vector2f renderPos((currPos.x * interpolation) + (prevPos.x * (1.0f - interpolation)), (currPos.y * interpolation) + (prevPos.y * (1.0f - interpolation)));

		_rect.x = (int)renderPos.x;
		_rect.y = (int)renderPos.y;
		_rect.w = ridgidBody.size.x;
		_rect.h = ridgidBody.size.y;
		this->SetDrawColor(renderable.color);
		SDL_RenderFillRect(_renderer, &_rect);
	}
}

void RenderRectSystem::SetDrawColor(Math::Vector4i color)
{
	SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
}