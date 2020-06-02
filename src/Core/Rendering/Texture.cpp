#include "Texture.hpp"

#include <iostream>
#include "../Util/Log.hpp"

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
		Log("ERROR: Bad renderer passed to texture class");
		return false;
	}

	this->_renderer = renderer;
	this->_filename = filename;

	SDL_Surface* tempSurface = IMG_Load(_filename.c_str());
	if (tempSurface == nullptr)
	{
		Log("ERROR: Unable to load image: %s", _filename.c_str());
		return false;
	}

	if ((_SDLTexture = SDL_CreateTextureFromSurface(_renderer, tempSurface)) == nullptr)
	{
		Log("ERROR: Unable to create texture");
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