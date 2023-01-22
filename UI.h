#pragma once

class UI
{
public:
	UI(int x, int y, int h, int w);		//assigns values to the destRect, and black variables, creates a surface
	~UI();								//frees the surface

	void updateUI(char* text);			//updates the displayed content
	void drawUI();						//renders the object

private:
	void DrawString(int x, int y, SDL_Surface* charset, char* text);

	SDL_Surface* tmpSurface;
	SDL_Texture* menuTexture;
	SDL_Rect destRect;
	int black;
};

