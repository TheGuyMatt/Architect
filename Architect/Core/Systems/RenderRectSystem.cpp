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

		_currPos = transform.position;
		_prevPos = transform.previous_pos;
		_worldPos = Math::Vector2f((_currPos.x * interpolation) + (_prevPos.x * (1.0f - interpolation)), (_currPos.y * interpolation) + (_prevPos.y * (1.0f - interpolation)));
		_renderPos = _worldPos - _camera;

		_rect.x = (int)_renderPos.x;
		_rect.y = (int)_renderPos.y;
		_rect.w = ridgidBody.size.x;
		_rect.h = ridgidBody.size.y;
		this->SetDrawColor(renderable.color);
		SDL_RenderDrawRect(_renderer, &_rect);
	}
}

void RenderRectSystem::SetDrawColor(Math::Vector4i color)
{
	SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
}