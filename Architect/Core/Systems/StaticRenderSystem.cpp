#include "StaticRenderSystem.hpp"

#include "../Components/Transform.hpp"
#include "../Components/RidgidBody.hpp"
#include "../Components/Renderable.hpp"

void StaticRenderSystem::Init(Coordinator *coordinator, SDL_Renderer *renderer)
{
	_coordinator = coordinator;
	_renderer = renderer;
}

void StaticRenderSystem::Update()
{
	for (auto const& entity : mEntities)
	{
		auto& transform = _coordinator->GetComponent<Transform>(entity);
		auto& ridgidBody = _coordinator->GetComponent<RigidBody>(entity);
		auto& renderable = _coordinator->GetComponent<Renderable>(entity);

		_rect.x = (int)transform.position.x;
		_rect.y = (int)transform.position.y;
		_rect.w = ridgidBody.size.x;
		_rect.h = ridgidBody.size.y;
		this->SetDrawColor(renderable.color);
		SDL_RenderFillRect(_renderer, &_rect);
	}
}

void StaticRenderSystem::SetDrawColor(Math::Vector4i color)
{
	SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
}