#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <vector>
#include <string>

#include "Texture.hpp"
#include "TileSet.hpp"

class ResourceManager
{
public:
	static bool Init(SDL_Renderer* renderer);
	static void CleanupTextures();
  static void CleanupTileSets();

	static Texture* getTexture(std::string ID);
  static TileSet* getTileSet(std::string ID);

private:
	static std::map<std::string, Texture*> _textureList;
	static void addTexture(SDL_Renderer* renderer, std::string ID, std::string filename);
	
	static std::map<std::string, TileSet*> _tileSetList;
  static void addTileSet(SDL_Renderer* renderer, std::string ID, std::string filename, Math::Vector2i tileDimensions);
};

#endif
