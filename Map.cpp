#include "Constants.h"
#include "Game.h"
#include "SDL.h"
#include "Textures.h"
#include "Map.h"

Map::Map(const char* texture, int l)
{
	mapTexture = Textures::loadTexture(texture);

	length = l;

	srcRect.x = 0;
	srcRect.y = l-WINDOW_HEIGHT;
	srcRect.h = WINDOW_HEIGHT;
	srcRect.w = WINDOW_WIDTH;

	destRect.x = 0;
	destRect.y = 0;
	destRect.h = WINDOW_HEIGHT;
	destRect.w = WINDOW_WIDTH;
}

void Map::updateMap()
{
	if(srcRect.y>0)
		srcRect.y-=speed;
	else
		srcRect.y = length/2;
}

void Map::drawMap()
{
	SDL_RenderCopy(Game::renderer, mapTexture, &srcRect, &destRect);
}

Map::~Map()
{
	SDL_DestroyTexture(mapTexture);
}

int Map::roadWidth(int y)
{
	int sectionLen = MAP_LENGHT / MAP_SECTIONS_NUMBER;
	int n = (Map::srcRect.y + y) / sectionLen % 2;

	if (n)
		return ROAD_WIDTH_1;
	return ROAD_WIDTH_2;
}