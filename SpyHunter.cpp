#include "Constants.h"
#include "Game.h"
#include "SDL.h"

void delay(unsigned int t0, const int frameDelay)
{
	unsigned int frameTime = SDL_GetTicks() - t0;
	if (frameTime < frameDelay)
		SDL_Delay(frameDelay - frameTime);
}

int main(int argc, char *argv[])
{
	const int frameDelay = 1000 / FPS;
	unsigned int t0;

	Game game = Game("Spy Hunter 2023", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	while (!game.quit())
	{
		game.init();
		while (!game.quit() && !game.newGame() && !game.over())
		{
			t0 = SDL_GetTicks();

			game.handleEvents();
			game.update();
			game.render();
			delay(t0, frameDelay);

			if (game.paused())
				game.pauseScreen();
		}
		game.clean();

		if (game.over())
			game.gameOverScreen();
	}

	return 0;
}