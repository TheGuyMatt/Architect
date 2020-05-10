#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <bitset>
#include "Coordinator.hpp"

class Window
{
public:
	Window() {}
	~Window();

	void create(const std::string &title, int width, int height, Coordinator *coordinator);

	const void clear(int r, int g, int b, int a);
	const void present();

	inline const bool isClosed() { return _closed; }
	inline const void close() { _closed = true; }

	inline SDL_Renderer* getRenderer() { return _renderer; }

private:
	bool Init();

	SDL_Window* _window = nullptr;
	SDL_Renderer * _renderer = nullptr;
	Coordinator *_coordinator;

	std::string _title;
	int _width = 800;
	int _height = 600;

	bool _closed = false;
};

#endif