#pragma once
#include "SDL.h"
#include "Constants.h"
#include "GameObject.h"
#include "Map.h"
#include "UI.h"

class Game {

public:
	Game(const char* title, int x, int y, int width, int height); //initialises SDL, creates window and renderer
	~Game();				//destroys the window, renderer and quits SDL

	void init();			//assigns values to variables and creates objects
	void handleEvents();	//handles events
	void update();			//updates objects
	void render();			//renders everything
	void clean();			//deletes objects

	void pauseScreen();		//handles the pause screen
	void gameOverScreen();	//handles the game over screen

	bool quit() { return isQuit; }
	bool newGame() { return isNew; }
	bool paused() { return isPaused; }
	bool over() { return isOver; }

	static SDL_Renderer *renderer;

private:
	GameObject* car;
	Map* map;
	UI* topmenu;
	UI* bottommenu;

	bool checkpoint();		//checks if the player has reached a new checkpoint

	SDL_Window* window;

	unsigned int timeStart, timePassed, timePauseStart;
	int score = 0;
	int leadinScore = 0;
	int lastCheckpoint = 0;
	int leadin = LEAD_IN_TIME;
	int lives = STARTER_LIVES;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;

	bool isQuit = false;
	bool isNew = false;
	bool isPaused = false;
	bool isOver = false;
};