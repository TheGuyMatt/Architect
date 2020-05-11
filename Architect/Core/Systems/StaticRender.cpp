#include "StaticRender.hpp"

#include "../Components/Transform.hpp"
#include "../Components/RidgidBody.hpp"
#include "../Components/Renderable.hpp"

void StaticRender::Init(Coordinator *coordinator, Camera* camera, SDL_Renderer *renderer)
{
	_coordinator = coordinator;
	_worldCamera = camera;
	_renderer = renderer;
}

void StaticRender::Update()
{
	for (auto const& entity : mEntities)
	{
		auto& transform = _coordinator->GetComponent<Transform>(entity);
		auto& ridgidBody = _coordinator->GetComponent<RigidBody>(entity);
		auto& renderable = _coordinator->GetComponent<Renderable>(entity);

		Math::Vector2f pos = Math::Vector2f(transform.position.x - _worldCamera->position.x,
											transform.position.y - _worldCamera->position.y);

		if (pos.x <= 800 && pos.x + ridgidBody.size.x >= 0 && pos.y <= 600 && pos.y + ridgidBody.size.y >= 0) //culling check
		{
			_rect.x = (int)pos.x;
			_rect.y = (int)pos.y;
			_rect.w = ridgidBody.size.x;
			_rect.h = ridgidBody.size.y;
			this->SetDrawColor(renderable.color);
			SDL_RenderFillRect(_renderer, &_rect);
		}
	}
}

void StaticRender::SetDrawColor(Math::Vector4i color)
{
	SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
}