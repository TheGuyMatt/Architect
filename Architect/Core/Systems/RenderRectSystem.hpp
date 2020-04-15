#ifndef RENDERRECTSYSTEM_HPP
#define RENDERRECTSYSTEM_HPP

#include <SDL.h>

#include "../ECS/System.hpp"
#include "../Coordinator.hpp"
#include "../Math/Vector2.hpp"
#include "../Math/Vector3.hpp"
#include "../Math/Vector4.hpp"

class RenderRectSystem : public System
{
public:
	void Init(Coordinator *coordinator, SDL_Renderer *renderer);
	void Update(float interpolation);

private:
	Coordinator *_coordinator;
	SDL_Renderer *_renderer;
	SDL_Rect _rect;

	void SetDrawColor(Math::Vector4i color);
};

#endif