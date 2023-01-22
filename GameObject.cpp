#include "Constants.h"
#include "Game.h"
#include "SDL.h"
#include "Textures.h"
#include "GameObject.h"

GameObject::GameObject(const char* texture, int x, int y, int w, int h)
{
	objTexture = Textures::loadTexture(texture);

	posx = x;
	posy = y;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = h;
	srcRect.w = w;

	destRect.x = posx;
	destRect.y = posy;
	destRect.h = h;
	destRect.w = w;
}

void GameObject::updateObject(int roadWidthFront, int roadWidthBack)
{
	if (left)
		posx-=2;
	if (right)
		posx+=2;
	destRect.x = posx;

	if (destRect.x<WINDOW_WIDTH / 2 - roadWidthFront / 2 || destRect.x + CAR_WIDTH>WINDOW_WIDTH / 2 + roadWidthFront / 2)
		isOffroad = true;
	else if (destRect.x<WINDOW_WIDTH / 2 - roadWidthBack / 2 || destRect.x + CAR_WIDTH>WINDOW_WIDTH / 2 + roadWidthBack / 2)
		isOffroad = true;
	else
		isOffroad = false;

	if (destRect.x + CAR_WIDTH<WINDOW_WIDTH / 2 - roadWidthFront / 2 || destRect.x>WINDOW_WIDTH / 2 + roadWidthFront / 2)
	{
		isCrashed = true;
		posx = WINDOW_WIDTH / 2 - CAR_WIDTH/2;
		destRect.x = posx;
	}
	else if (destRect.x + CAR_WIDTH<WINDOW_WIDTH / 2 - roadWidthBack / 2 || destRect.x>WINDOW_WIDTH / 2 + roadWidthBack / 2)
	{
		isCrashed = true;
		posx = WINDOW_WIDTH / 2 - CAR_WIDTH / 2;
		destRect.x = posx;
	}
	else
		isCrashed = false;
}

void GameObject::render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(objTexture);
}