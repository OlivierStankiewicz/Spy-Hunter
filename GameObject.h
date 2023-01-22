#pragma once

class GameObject
{
public:
	GameObject(const char* texture, int x, int y, int w, int h);	//loads the object texture and assignes values to variables
	~GameObject();		//destroys the object texture

	void updateObject(int roadWidthFront, int roadWidthBack);		//updates the object position and the isOffroad and isCrashed variables
	void render();		//renders the object

	int objectY() { return posy; }
	bool offroad() { return isOffroad; }
	bool crashed() { return isCrashed; }
	
	bool left = false;
	bool right = false;

private:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

	int posx, posy;

	bool isOffroad = false;
	bool isCrashed = false;
};

