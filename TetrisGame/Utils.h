#ifndef UTILS_H
#define UTILS_H
#include <SDL.h>
#include <SDL_image.h>

constexpr auto TILE_W = 20;
constexpr auto TILE_H = 20;
constexpr auto SCREEN_ROW = 40;
constexpr auto SCREEN_COL = 20;

enum {background, border, I_block, J_block, L_block, O_block, S_block, T_block, Z_block, horizantal, vertical, up, right, down, left, empty, block_tile};

namespace TextureManager {
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);

	void renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect);
}


#endif