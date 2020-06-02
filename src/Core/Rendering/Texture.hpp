#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <string>

class Texture
{
public:
	Texture() {}
	~Texture();

	bool load(SDL_Renderer* renderer, std::string filename);

	void render(int x, int y);
	void render(int x, int y, int width, int height);
	void render(int x, int y, int width, int height, int sx, int sy, int swidth, int sheight);

	int getWidth() { return _width; }
	int getHeight() { return _height; }

private:
	std::string _filename;
	int _width = 0, _height = 0;
	SDL_Renderer* _renderer = nullptr;
	SDL_Texture* _SDLTexture = nullptr;
};

#endif