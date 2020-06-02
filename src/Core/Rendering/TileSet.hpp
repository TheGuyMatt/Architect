#ifndef TILESET_HPP
#define TILESET_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <string>

class TileSet
{
public:
	TileSet() {}
	~TileSet();

	bool load(SDL_Renderer* renderer, std::string filename);

	void render();

	int getWidth() { return _width; }
	int getHeight() { return _height; }
	int getTileWidth() { return _tileWidth; }
	int getTileHeight() { return _tileHeight; }
	int getTotalColumns() { return _totalColumns; }
	int getTotalRows() { return _totalRows; }

private:
	std::string _filename;
	int _width = 0;
	int _height = 0;
	int _tileWidth = 0;
	int _tileHeight = 0;
	int _totalColumns = 0;
	int _totalRows = 0;
	SDL_Renderer* _renderer;
	SDL_Texture* _SDLTexture;
};

#endif