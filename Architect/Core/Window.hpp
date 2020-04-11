#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>
#include <SDL.h>

class Window
{
public:
	Window(const std::string &title, int width, int height);
	~Window();

	void pollEvents();
	inline const bool isClosed() { return _closed; }

private:
	bool Init();

	SDL_Window* _window = nullptr;

	std::string _title;
	int _width = 800;
	int _height = 600;

	bool _closed = false;
};

#endif