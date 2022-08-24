#include "Utils.h"

SDL_Texture* TextureManager::loadTexture(SDL_Renderer* renderer, const char* path) {
	SDL_Surface* tempSurface = IMG_Load(path);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	SDL_FreeSurface(tempSurface);
	return texture;
}

void TextureManager::renderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect) {
	SDL_RenderCopy(renderer, texture, srcRect, destRect);
}
