#include "Texture.hpp"

#include <iostream>

Texture::~Texture()
{
	if (_SDLTexture != nullptr)
	{
		SDL_DestroyTexture(_SDLTexture);
		_SDLTexture = nullptr;
	}
}

bool Texture::load(SDL_Renderer* renderer, std::string filename)
{
	if (renderer == nullptr)
	{
		std::cerr << "Bad renderer passed to texture class\n";
		return false;
	}

	this->_renderer = renderer;
	this->_filename = filename;

	SDL_Surface* tempSurface = IMG_Load(_filename.c_str());
	if (tempSurface == nullptr)
	{
		std::cerr << "Unable to load image\n";
		return false;
	}

	if ((_SDLTexture = SDL_CreateTextureFromSurface(_renderer, tempSurface)) == nullptr)
	{
		std::cerr << "Unable to create texture\n";
		return false;
	}

	SDL_QueryTexture(_SDLTexture, nullptr, nullptr, &_width, &_height);
	SDL_FreeSurface(tempSurface);
	return true;
}

void Texture::render(int x, int y)
{
	render(x, y, _width, _height);
}

void Texture::render(int x, int y, int width, int height)
{
	SDL_Rect destination = { x, y, width, height };

	SDL_RenderCopy(_renderer, _SDLTexture, nullptr, &destination);
}

void Texture::render(int x, int y, int width, int height, int sx, int sy, int swidth, int sheight)
{
	SDL_Rect destination = { x, y, width, height };
	SDL_Rect source = { sx, sy, swidth, sheight };

	SDL_RenderCopy(_renderer, _SDLTexture, &source, &destination);
}