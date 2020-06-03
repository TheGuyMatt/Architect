#ifndef TILESET_HPP
#define TILESET_HPP

#include <SDL.h>
#include <SDL_image.h>

#include "../Math/Vector2.hpp"
#include "../Rendering/Texture.hpp"

class TileSet
{
public:
	TileSet() {}
	~TileSet();

	bool load(Texture *texture, Math::Vector2i tileDimensions);

	void render(int col, int row, int x, int y);
	void render(int col, int row, int x, int y, int width, int height);

  Math::Vector2i getDimensions() { return _dimensions; }
  Math::Vector2i getTileDimensions() { return _tileDimensions; }
  Math::Vector2i getTiles() { return _tiles; }

private:
  Texture *_texture;
  Math::Vector2i _dimensions = Math::Vector2i();
  Math::Vector2i _tileDimensions = Math::Vector2i();
	Math::Vector2i _tiles = Math::Vector2i();
};

#endif
