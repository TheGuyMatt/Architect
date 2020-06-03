#include "TileSet.hpp"

#include <iostream>
#include "../Util/Log.hpp"

TileSet::~TileSet()
{

}

bool TileSet::load(Texture *texture, Math::Vector2i tileDimensions)
{
  if (texture == nullptr)
  {
    Log("ERROR: Bad texture passed to tileset class");
    return false;
  }

  this->_texture = texture;
  this->_dimensions = Math::Vector2i(texture->getWidth(), texture->getHeight());
  this->_tileDimensions = tileDimensions;
  this->_tiles = _dimensions / _tileDimensions;
  return true;
}

void TileSet::render(int col, int row, int x, int y)
{
  _texture->render(x, y, _tileDimensions.x, _tileDimensions.y, col * _tileDimensions.x, row * _tileDimensions.y, _tileDimensions.x, _tileDimensions.y);
}

void TileSet::render(int col, int row, int x, int y, int width, int height)
{
  _texture->render(x, y, width, height, col * _tileDimensions.x, row * _tileDimensions.y, _tileDimensions.x, _tileDimensions.y);
}
