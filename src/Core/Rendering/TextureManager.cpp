#include "TextureManager.hpp"

#include <iostream>
#include "../Util/StringHandler.hpp"
#include "../Util/FileManager.hpp"
#include "../Util/Log.hpp"

std::map<std::string, Texture*> TextureManager::_textureList;
std::map<std::string, TileSet*> TextureManager::_tileSetList;

bool TextureManager::Init(SDL_Renderer* renderer)
{
  CleanupTextures();
  CleanupTileSets();

	if (renderer == nullptr) return false;

  //Load all textures into texture manager
  std::string ResPath = "../Resources/Textures/";
	std::vector<std::string> textureFiles;
  textureFiles.push_back(ResPath + "PineTree.png");
  textureFiles.push_back(ResPath + "Scarecrow.png");
  textureFiles.push_back(ResPath + "sky.png");
  textureFiles.push_back(ResPath + "Zip.png");

	for (auto filename : textureFiles)
	{
		std::string ext = FileManager::getFileNameExt(filename);
		std::string ID = FileManager::getFileNameWithoutExt(filename);

		if (ext != "png") continue;

		addTexture(renderer, ID, filename);

		Log("Added texture to manager \'%s\' at path %s", ID.c_str(), filename.c_str());
	}

  //Load all textures into texture manager
  ResPath = "../Resources/TileSets/";
	std::vector<std::string> tileSetfiles;
  tileSetfiles.push_back(ResPath + "TempTileSet.png");

	for (auto filename : tileSetfiles)
	{
		std::string ext = FileManager::getFileNameExt(filename);
		std::string ID = FileManager::getFileNameWithoutExt(filename);

		if (ext != "png") continue;

		addTileSet(renderer, ID, filename, Math::Vector2i(32, 32));

		Log("Added tileset to manager \'%s\' at path %s", ID.c_str(), filename.c_str());
	}

	return true;
}

void TextureManager::CleanupTextures()
{
	if (_textureList.size() <= 0) return;

	for (auto& Iterator : _textureList)
	{
		Texture* tempTexture = (Texture*)Iterator.second;

		if (tempTexture != nullptr)
		{
			delete tempTexture;
			tempTexture = nullptr;
		}
	}

	_textureList.clear();
}

void TextureManager::CleanupTileSets()
{
	if (_tileSetList.size() <= 0) return;

	for (auto& Iterator : _tileSetList)
	{
		TileSet* tempTileSet = (TileSet*)Iterator.second;

		if (tempTileSet != nullptr)
		{
			delete tempTileSet;
			tempTileSet = nullptr;
		}
	}

	_tileSetList.clear();
}

Texture* TextureManager::getTexture(std::string ID)
{
	if (_textureList.find(ID) == _textureList.end()) return 0;

	return _textureList[ID];
}

TileSet* TextureManager::getTileSet(std::string ID)
{
	if (_tileSetList.find(ID) == _tileSetList.end()) return 0;

	return _tileSetList[ID];
}

void TextureManager::addTexture(SDL_Renderer* renderer, std::string ID, std::string filename)
{
	if ( ID == "" ) return;

	Texture* newTexture = new Texture();
	if (newTexture->load(renderer, filename) == false)
	{
		Log("ERROR: Unable to load texture: %s", filename.c_str());
		return;
	}

	_textureList[ID] = newTexture;
}

void TextureManager::addTileSet(SDL_Renderer* renderer, std::string ID, std::string filename, Math::Vector2i tileDimensions)
{
	if ( ID == "" ) return;

	Texture* newTexture = new Texture();
	if (newTexture->load(renderer, filename) == false)
	{
		Log("ERROR: Unable to load texture: %s", filename.c_str());
		return;
	}

  TileSet* newTileSet = new TileSet();
  if (newTileSet->load(newTexture, tileDimensions) == false) return;

	_tileSetList[ID] = newTileSet;
}
