#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <SDL.h>
#include <bitset>
#include "InputButtons.hpp"
#include "../Coordinator.hpp"

#include "../Window.hpp"

class InputManager
{
public:
	InputManager() {}
	~InputManager() {}

	void Init(Coordinator *coordinator, Window *window);
	void Update();

private:
	Coordinator *_coordinator;
	Window *_window;

	SDL_Event evnt;

	std::bitset<8> _buttons;
	bool _buttonStateChanged = true;

	void buttonEvent();
};

#endif