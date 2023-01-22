#include "Game.h"
#include "SDL.h"
#include "UI.h"

UI::UI(int x, int y, int h, int w)
{
	destRect.x = x;
	destRect.y = y;
	destRect.h = h;
	destRect.w = w;
	tmpSurface = SDL_CreateRGBSurface(0, destRect.w, destRect.h, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	black = SDL_MapRGB(tmpSurface->format, 0x00, 0x00, 0x00);
}

void UI::updateUI(char* text)
{
	SDL_Surface* charst = SDL_LoadBMP("assets/cs8x8.bmp");

	SDL_FillRect(tmpSurface, NULL, black);
	DrawString(8, 8, charst, text);
	menuTexture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);

	SDL_FreeSurface(charst);
}

void UI::drawUI()
{
	SDL_RenderCopy(Game::renderer, menuTexture, NULL, &destRect);
	SDL_DestroyTexture(menuTexture);
}

UI::~UI()
{
	SDL_FreeSurface(tmpSurface);
}

void UI::DrawString(int x, int y, SDL_Surface* charset, char* text)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, tmpSurface, &d);
		x += 8;
		text++;
	};
};