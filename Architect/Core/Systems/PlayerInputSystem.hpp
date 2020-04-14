#ifndef PLAYERINPUTSYSTEM_HPP
#define PLAYERINPUTSYSTEM_HPP

#include <SDL.h>

#include "../ECS/System.hpp"
#include "../Coordinator.hpp"

class PlayerInputSystem : public System
{
public:
	void Init(Coordinator *coordinator);
	void Update();

private:
	Coordinator *_coordinator = nullptr;

	//input variables
	std::bitset<8> _buttons;
	void InputListener(Event &event);
};

#endif