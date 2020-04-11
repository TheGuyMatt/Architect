#ifndef RENDERRECTSYSTEM_HPP
#define RENDERRECTSYSTEM_HPP

#include <SDL.h>

#include "../ECS/System.hpp"
#include "../ECS/Coordinator.hpp"

class RenderRectSystem : public System
{
public:
	void Init(Coordinator *coordinator, SDL_Renderer *renderer);
	void Update(float interpolation);

private:
	Coordinator *_coordinator;
	SDL_Renderer *_renderer;
};

#endif