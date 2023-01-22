#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include <stdio.h>

SDL_Renderer *Game::renderer = nullptr;

Game::Game(const char* title, int posx, int posy, int width, int height)
{
	int flags = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, posx, posy, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		isQuit = false;
	}

	else
	{
		isQuit = true;
	}
}

void Game::init()
{
	leadin = LEAD_IN_TIME;
	lives = STARTER_LIVES;
	score = 0;
	leadinScore = 0;
	lastCheckpoint = 0;
	isNew = false;
	isOver = false;
	isPaused = false;

	map = new Map("assets/spymap2.bmp", MAP_LENGHT);
	car = new GameObject("assets/wcar.bmp", WINDOW_WIDTH/2-CAR_WIDTH/2, WINDOW_HEIGHT/2-CAR_HEIGHT/2, CAR_WIDTH, CAR_HEIGHT);
	topmenu = new UI(MENU_TOP_X, MENU_TOP_Y, MENU_TOP_HEIGHT, MENU_TOP_WIDTH);
	bottommenu = new UI(MENU_BOTTOM_X, MENU_BOTTOM_Y, MENU_BOTTOM_HEIGHT, MENU_BOTTOM_WIDTH);

	timeStart = SDL_GetTicks();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isQuit = true;
		break;

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) isQuit = true;
		else if (event.key.keysym.sym == SDLK_LEFT) car->left = true;
		else if (event.key.keysym.sym == SDLK_RIGHT) car->right = true;
		else if (event.key.keysym.sym == SDLK_UP) map->speed = 3;
		else if (event.key.keysym.sym == SDLK_DOWN) map->speed = 1;
		else if (event.key.keysym.sym == SDLK_n) isNew = true;
		else if (event.key.keysym.sym == SDLK_p) isPaused = true;
		else if (event.key.keysym.sym == SDLK_f) isOver = true;
		break;

	case SDL_KEYUP:
		car->left = false;
		car->right = false;
		map->speed = 2;
		break;

	default:
		break;
	}
}

void Game::update()
{
	map->updateMap();
	car->updateObject(map->roadWidth(car->objectY()), map->roadWidth(car->objectY() + CAR_HEIGHT));

	if (!car->offroad())
	{
		score+=map->speed;
	}

	char text[128];
	timePassed = (SDL_GetTicks() - timeStart) / 1000;
	hours = timePassed / 60 / 60;
	minutes = (timePassed - hours * 60 * 60) / 60;
	seconds = timePassed - hours * 60 * 60 - minutes * 60;
	sprintf(text, "Olivier Stankiewicz                   czas gry: %02d:%02d:%02d   wynik: %d", hours, minutes, seconds, score);
	topmenu->updateUI(text);

	if (leadin > 0)
	{
		leadin = LEAD_IN_TIME - timePassed;
		sprintf(text, "Nieogranicze samochody: %ds", leadin);
		leadinScore = score;
	}
	else
	{
		if (car->crashed())
		{
			if (lives > 1)
				lives--;
			else
				isOver = true;
		}
		else if (checkpoint())
		{
			lives++;
		}
		sprintf(text, "Liczba samochodow: %d", lives);
	}
	bottommenu->updateUI(text);
}

void Game::render()
{
	SDL_RenderClear(renderer);
	map->drawMap();
	car->render();
	topmenu->drawUI();
	bottommenu->drawUI();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete map;
	delete car;
	delete topmenu;
	delete bottommenu;
}

Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::checkpoint()
{
	int dist = CHECKPOINT_DISTANCE;
	if ((score - leadinScore) % dist < 3 && (score - leadinScore) / dist != lastCheckpoint)
	{
		lastCheckpoint = (score - leadinScore) / dist;
		return true;
	}
	return false;
}

void Game::pauseScreen()
{
	timePauseStart = SDL_GetTicks();
	char text[128];

	UI pauseMenuTop(PAUSE_MENU_A_X, PAUSE_MENU_A_Y, PAUSE_MENU_A_HEIGHT, PAUSE_MENU_A_WIDTH);
	sprintf(text, "PAUZA");
	pauseMenuTop.updateUI(text);

	UI pauseMenuP(PAUSE_MENU_B_X, PAUSE_MENU_B_Y, PAUSE_MENU_B_HEIGHT, PAUSE_MENU_B_WIDTH);
	sprintf(text, "p - powrot do gry");
	pauseMenuP.updateUI(text);

	UI pauseMenuN(PAUSE_MENU_B_X, PAUSE_MENU_B_Y + 40, PAUSE_MENU_B_HEIGHT, PAUSE_MENU_B_WIDTH);
	sprintf(text, "n - nowa gra");
	pauseMenuN.updateUI(text);

	UI pauseMenuE(PAUSE_MENU_B_X, PAUSE_MENU_B_Y + 80, PAUSE_MENU_B_HEIGHT, PAUSE_MENU_B_WIDTH);
	sprintf(text, "esc - wyjscie");
	pauseMenuE.updateUI(text);

	UI pauseMenuF(PAUSE_MENU_B_X, PAUSE_MENU_B_Y + 120, PAUSE_MENU_B_HEIGHT, PAUSE_MENU_B_WIDTH);
	sprintf(text, "f - koniec gry");
	pauseMenuF.updateUI(text);

	sprintf(text, "Olivier Stankiewicz 193454             czas gry: %02d:%02d:%02d   wynik: %d", hours, minutes, seconds, score);
	topmenu->updateUI(text);

	if (leadin > 0)
		sprintf(text, "Nieogranicze samochody: %ds", leadin);
	else
		sprintf(text, "Liczba samochodow: %d", lives);
	bottommenu->updateUI(text);

	SDL_RenderClear(renderer);
	map->drawMap();
	car->render();
	topmenu->drawUI();
	bottommenu->drawUI();
	pauseMenuTop.drawUI();
	pauseMenuP.drawUI();
	pauseMenuN.drawUI();
	pauseMenuE.drawUI();
	pauseMenuF.drawUI();
	SDL_RenderPresent(renderer);

	while (isPaused && !isQuit && !isOver)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			isQuit = true;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) isQuit = true;
			else if (event.key.keysym.sym == SDLK_n)
			{
				isNew = true;
				isPaused = false;
			}
			else if (event.key.keysym.sym == SDLK_p) isPaused = false;
			else if (event.key.keysym.sym == SDLK_f) isOver = true;
			break;

		default:
			break;
		}
	}

	timeStart += SDL_GetTicks() - timePauseStart;
}

void Game::gameOverScreen()
{
	char text[128];

	UI overMenuTop(OVER_MENU_A_X, OVER_MENU_A_Y, OVER_MENU_A_HEIGHT, OVER_MENU_A_WIDTH);
	sprintf(text, "KONIEC GRY");
	overMenuTop.updateUI(text);

	UI overMenuN(OVER_MENU_B_X, OVER_MENU_B_Y, OVER_MENU_B_HEIGHT, OVER_MENU_B_WIDTH);
	sprintf(text, "n - nowa gra");
	overMenuN.updateUI(text);

	UI overMenuE(OVER_MENU_B_X, OVER_MENU_B_Y + 40, OVER_MENU_B_HEIGHT, OVER_MENU_B_WIDTH);
	sprintf(text, "esc - wyjscie");
	overMenuE.updateUI(text);

	SDL_RenderClear(renderer);
	overMenuTop.drawUI();
	overMenuN.drawUI();
	overMenuE.drawUI();
	SDL_RenderPresent(renderer);

	while (!isNew && !isQuit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			isQuit = true;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) isQuit = true;
			else if (event.key.keysym.sym == SDLK_n) isNew = true;
			break;

		default:
			break;
		}
	}
}