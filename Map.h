#pragma once

class Map
{
public:
	Map(const char* texture, int l);	//loads the map texture and assignes values to variables
	~Map();

	void updateMap();		//updates the map
	void drawMap();			//renders the map
	int roadWidth(int y);	//returns the width of the road at a given y position on the screen

	int speed = 2;

private:
	SDL_Rect srcRect, destRect;
	SDL_Texture* mapTexture;

	int length;
};

