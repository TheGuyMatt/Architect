#ifndef STATICRENDERSYSTEM_HPP
#define STATICRENDERSYSTEM_HPP

#include <SDL.h>

#include "../ECS/System.hpp"
#include "../Coordinator.hpp"
#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Vector4.hpp"
#include "../Camera.hpp"

class StaticRenderSystem : public System
{
public:
	void Init(Coordinator *coordinator, Camera* camera, SDL_Renderer *renderer);
	void Update();

private:
	Coordinator *_coordinator;
	Camera* _worldCamera;
	SDL_Renderer *_renderer;
	SDL_Rect _rect;

	void SetDrawColor(Math::Vector4i color);
};

#endif