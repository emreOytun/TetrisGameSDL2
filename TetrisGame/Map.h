#pragma once
#include <vector>
#include <array>
#include <SDL.h>

constexpr auto MAX_BLOCK_NUMBER = 7;

class Block;

class Map
{
private:
	std::vector<std::vector<int>> map;
	SDL_Renderer* renderer;

	SDL_Texture* border_text;
	SDL_Texture* background_text;
	std::array<SDL_Texture*, MAX_BLOCK_NUMBER> block_textures;
	SDL_Rect background_rect;


public:
	Map(SDL_Renderer* renderer);
	~Map();
	Map(const Map&) = delete;
	Map& operator=(const Map&) = delete;

	void placeBlock(const Block& block);
	bool checkBottomCollision(const Block& block);
	bool checkTopCollision(const Block& block);

	void render();
};

