#include "TextureManager.hpp"

#include <iostream>
#include "../Util/StringHandler.hpp"
#include "../Util/FileManager.hpp"

std::map<std::string, Texture*> TextureManager::_textureList;

bool TextureManager::Init(SDL_Renderer* renderer)
{
	Cleanup();

	if (renderer == nullptr) return false;

	std::vector<std::string> files = FileManager::getFilesInFolder("Resources/Textures");

	for (auto filename : files)
	{
		std::string ext = FileManager::getFileNameExt(filename);
		std::string ID = FileManager::getFileNameWithoutExt(filename);

		if (ext != "png") continue;

		addTexture(renderer, ID, filename);
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
		std::cerr << "Unable to load texture\n";
		std::cout << filename << "\n";
		return;
	}

	_textureList[ID] = newTexture;
}