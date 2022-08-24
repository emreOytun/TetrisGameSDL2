#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Utils.h"


class Block;
class Map;

class Game
{

public:
	Game();
	~Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void init(const char* title, int xpos, int ypos, int width, int heigth, bool fullscreen);	
	
	void handleEvents();
	void fixCollision();
	void update();
	void render();

	bool running() const { return isRunning; }	

	
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Event event;
	SDL_Renderer* renderer;

	Block* block;
	Map* map;
	int total_points;
	
	Block* generateRandomBlock();
	void clean();
};


#endif

