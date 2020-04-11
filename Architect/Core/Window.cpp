#include "Window.hpp"

Window::Window(const std::string &title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	//initialize window
	//close window if failed to initialize
	if (!Init())
	{
		_closed = true;
	}
}

Window::~Window()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
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

		default:
			break;
		}
	}
}