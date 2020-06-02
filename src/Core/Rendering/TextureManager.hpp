#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <map>
#include <vector>
#include <string>

#include "Texture.hpp"

class TextureManager
{
public:
	static bool Init(SDL_Renderer* renderer);
	static void Cleanup();

	static Texture* get(std::string ID);

private:
	static std::map<std::string, Texture*> _textureList;
	static void addTexture(SDL_Renderer* renderer, std::string ID, std::string filename);
};

#endif