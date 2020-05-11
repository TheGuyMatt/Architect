#include "Window.hpp"

#include "Input/InputButtons.hpp"

Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
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
	//tell coordinator to quit if window closed during initialization
	if (_closed) _coordinator->SendEvent(Events::Window::QUIT);
}

bool Window::Init()
{
	//initialize SDL_VIDEO
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed to initialize SDL_VIDEO\n";
		return false;
	}

	//initialize SDL_image
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cerr << "Failed to initalize SDL_image\n";
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

const void Window::clear(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
	SDL_RenderClear(_renderer);
}

const void Window::present()
{
	SDL_RenderPresent(_renderer);
}