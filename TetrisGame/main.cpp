#include <iostream>
#include "Game.h"
#include "Utils.h"
#include <time.h>

int main(int argc, char* argv[]) {
	srand(time(0));

	/* ADJUSTING FPS AS 60fps : Needs the variables below. Calculate the frame time in the main, and give it delay if needed. */
	const int FPS = 10;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	Game game;
	game.init("TetrisGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TILE_W * SCREEN_COL, TILE_H * SCREEN_ROW, false);

	do {
		frameStart = SDL_GetTicks();

		game.handleEvents();
		game.fixCollision();
		game.render();

		game.handleEvents();
		game.fixCollision();
		game.render();

		game.handleEvents();
		game.fixCollision();
		game.render();

		game.handleEvents();
		game.fixCollision();
		game.render();

		game.handleEvents();
		game.update();
		game.fixCollision();
		game.render();


		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) {
			SDL_Delay(frameDelay - frameTime);
		}

	} while (game.running());



	return 0;
}