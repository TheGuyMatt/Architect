#include "InputManager.hpp"

void InputManager::Init(Coordinator *coordinator)
{
	_coordinator = coordinator;
}

void InputManager::Update()
{
	while (SDL_PollEvent(&evnt) != 0)
	{
		_buttonStateChanged = true;

		switch (evnt.type)
		{
		case SDL_QUIT:
			_coordinator->SendEvent(Events::Window::QUIT);
			break;

		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym)
			{

			case SDLK_ESCAPE:
				_coordinator->SendEvent(Events::Window::QUIT);
				break;
			case SDLK_w:
				_buttons.set(static_cast<std::size_t>(InputButtons::W));
				break;
			case SDLK_a:
				_buttons.set(static_cast<std::size_t>(InputButtons::A));
				break;
			case SDLK_s:
				_buttons.set(static_cast<std::size_t>(InputButtons::S));
				break;
			case SDLK_d:
				_buttons.set(static_cast<std::size_t>(InputButtons::D));
				break;
			default:
				_buttonStateChanged = false;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (evnt.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				_coordinator->SendEvent(Events::Window::QUIT);
				break;
			case SDLK_w:
				_buttons.reset(static_cast<std::size_t>(InputButtons::W));
				break;
			case SDLK_a:
				_buttons.reset(static_cast<std::size_t>(InputButtons::A));
				break;
			case SDLK_s:
				_buttons.reset(static_cast<std::size_t>(InputButtons::S));
				break;
			case SDLK_d:
				_buttons.reset(static_cast<std::size_t>(InputButtons::D));
				break;
			default:
				_buttonStateChanged = false;
				break;
			}
			break;

		default:
			_buttonStateChanged = false;
			break;
		}

		if (_buttonStateChanged)
		{
			buttonEvent();
		}
	}
}

void InputManager::buttonEvent()
{
	Event event(Events::Window::INPUT);
	event.SetParam(Events::Window::Input::INPUT, _buttons);
	_coordinator->SendEvent(event);
}