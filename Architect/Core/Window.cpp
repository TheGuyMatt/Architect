#include "Window.hpp"

#include "Input/InputButtons.hpp"

Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Window::create(const std::string &title, int width, int height, Coordinator *coordinator)
{
	_title = title;
	_width = width;
	_height = height;
	_coordinator = coordinator;

	//initialize window
	//close window if failed to initialize
	_closed = !Init();
}

bool Window::Init()
{
	//initialize SDL_VIDEO
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed to initialize SDL_VIDEO\n";
		return false;
	}

	//create the window
	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);
	if (_window == nullptr)
	{
		std::cerr << "Failed to create window\n";
		return false;
	}
	
	//create the renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
	{
		std::cerr << "Failed to create renderer\n";
		return false;
	}

	return true;
}

void Window::pollEvents()
{
	SDL_Event evnt;

	if (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_closed = true;
			break;

		case SDL_KEYDOWN:
			_buttonStateChanged = true;
			switch (evnt.key.keysym.sym)
			{

			case SDLK_ESCAPE:
				_closed = true;
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

				if (_buttonStateChanged)
				{
					Event event(Events::Window::INPUT);
					event.SetParam(Events::Window::Input::INPUT, _buttons);
					_coordinator->SendEvent(event);
				}
			}
			break;

		case SDL_KEYUP:
			_buttonStateChanged = true;
			switch (evnt.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				_closed = true;
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

				if (_buttonStateChanged)
				{
					Event event(Events::Window::INPUT);
					event.SetParam(Events::Window::Input::INPUT, _buttons);
					_coordinator->SendEvent(event);
				}
			}
			break;

		default:
			break;
		}
	}
}

const void Window::clear(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
	SDL_RenderClear(_renderer);
}

const void Window::present()
{
	SDL_RenderPresent(_renderer);
}