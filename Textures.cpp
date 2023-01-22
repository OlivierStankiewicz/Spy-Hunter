#include "Game.h"
#include "SDL.h"
#include "Textures.h"

SDL_Texture* Textures::loadTexture(const char* fileName)
{
	SDL_Surface *tmpSurface = SDL_LoadBMP(fileName);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return texture;
}