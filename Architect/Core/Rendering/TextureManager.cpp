#include "TextureManager.hpp"

#include <iostream>

std::map<std::string, Texture*> TextureManager::_textureList;

bool TextureManager::Init(SDL_Renderer* renderer)
{
	Cleanup();

	if (renderer == nullptr) return false;

	std::vector<std::string> files;
	files.push_back("Resources/PineTree.png");
	files.push_back("Resources/Scarecrow.png");
	files.push_back("Resources/sky.png");
	files.push_back("Resources/TempTileSet.png");
	files.push_back("Resources/Zip.png");

	for (auto filename : files)
	{
		std::string ext = getFileNameExt(filename);
		std::string ID = getFileNameWithoutExt(filename);

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

std::vector<std::string> TextureManager::explodeStr(std::string str, const std::string& separator)
{
	std::vector<std::string> results;

	int found;
	found = str.find_first_of(separator);
	while (found != std::string::npos)
	{
		if (found > 0) results.push_back(str.substr(0, found));

		str = str.substr(found + 1);
		found = str.find_first_of(separator);
	}

	if (str.length() > 0) results.push_back(str);

	return results;
}

std::string TextureManager::getFileNameWithoutExt(std::string filename)
{
	std::vector<std::string> parts = explodeStr(filename, "/");
	std::string newFilename = parts[parts.size() - 1];

	parts = explodeStr(newFilename, ".");
	newFilename = parts[0];
	return newFilename;
}

std::string TextureManager::getFileNameExt(std::string filename)
{
	std::vector<std::string> parts = explodeStr(filename, ".");

	return (parts.size() <= 1 ? "" : parts[parts.size() - 1]);
}