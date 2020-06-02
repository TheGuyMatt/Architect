#include "TextureManager.hpp"

#include <iostream>
#include "../Util/StringHandler.hpp"
#include "../Util/FileManager.hpp"
#include "../Util/Log.hpp"

std::map<std::string, Texture*> TextureManager::_textureList;

bool TextureManager::Init(SDL_Renderer* renderer)
{
	Cleanup();

	if (renderer == nullptr) return false;

  std::string ResPath = "../../../Resources/Textures/";
	std::vector<std::string> files;
  files.push_back(ResPath + "PineTree.png");
  files.push_back(ResPath + "Scarecrow.png");
  files.push_back(ResPath + "sky.png");
  files.push_back(ResPath + "TempTileSet.png");
  files.push_back(ResPath + "Zip.png");

	for (auto filename : files)
	{
		std::string ext = FileManager::getFileNameExt(filename);
		std::string ID = FileManager::getFileNameWithoutExt(filename);

		if (ext != "png") continue;

		addTexture(renderer, ID, filename);

		Log("Added texture to manager \'%s\' at path %s", ID.c_str(), filename.c_str());
	}

	return true;
}

void TextureManager::Cleanup()
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

Texture* TextureManager::get(std::string ID)
{
	if (_textureList.find(ID) == _textureList.end()) return 0;

	return _textureList[ID];
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
