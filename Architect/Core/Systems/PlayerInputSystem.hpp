#ifndef PLAYERINPUTSYSTEM_HPP
#define PLAYERINPUTSYSTEM_HPP

#include <SDL.h>

#include "../ECS/System.hpp"
#include "../Coordinator.hpp"

class PlayerInputSystem : public System
{
public:
	void Init(Coordinator *coordinator);
	void Update(float dt);

private:
	Coordinator *_coordinator;
};

#endif