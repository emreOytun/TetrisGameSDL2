#include "Game.h"
#include "Map.h"
#include "Block.h"
#include <time.h>

Game::Game() = default;
Game::~Game() {
	clean();
	std::cout << "GAME DESTROYED!" << std::endl;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	isRunning = false;

	// Always check after initializing SDL, windows, renderers etc.

	int flags{ 0 };
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

	// Create and Check if sdl is initialized successfuly.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!..." << std::endl;

		// Create and Check if window is initialized successfully.
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;

			// Create and Check if renderer is initialized successfully.
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				std::cout << "Renderer created!" << std::endl;

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}

			isRunning = true; // If everything is initialized, then mark isRunning as true.
		}
	}

	// Initialize texture here for now. After we'll create TextureManager to initialize/delete all textures.
	if (isRunning) {
		map = new Map(renderer);
		block = generateRandomBlock();
	}

	std::cout << "GAME created!" << std::endl;
}

void Game::handleEvents() {

	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_w) {
			block->rotate();
		}

		else if (event.key.keysym.sym == SDLK_s) {
			block->setSpeed(2);
			block->update();
		}

		else if (event.key.keysym.sym == SDLK_d) {
			block->moveHorizantal(right);
		}

		else if (event.key.keysym.sym == SDLK_a) {
			block->moveHorizantal(left);
		}

		break;

	case SDL_KEYUP :
		if (event.key.keysym.sym == SDLK_s) {
			block->setSpeed(1);
		}


	default:
		break;
	}

}

void Game::fixCollision() {
	if (map->checkBottomCollision(*block) == true) {
		
		do {
			block->back_one_step();
		} while (map->checkBottomCollision(*block) == true);

		if (map->checkTopCollision(*block) == true) {
			std::cout << "!!!!!!!!! ---- GAME OVER ----- !!!!!!!!!\n";
			SDL_Delay(1000);
			
			delete block;
			isRunning = false;
		}

		else {
			map->placeBlock(*block);
			//IMPLEMENT map->checkLines();
			
			delete block;
			block = generateRandomBlock();
		}
	
	}
}

void Game::update() {
	
	block->update();
}

void Game::render() {
	SDL_RenderClear(renderer); // Clear render buffer

	map->render();
	block->render(renderer);

	SDL_RenderPresent(renderer);
}

Block* Game::generateRandomBlock() {
	int block_id = rand() % 7;
	return new Block(renderer, I_block + block_id);
}

void Game::clean() {
	delete map;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!" << std::endl;
}
