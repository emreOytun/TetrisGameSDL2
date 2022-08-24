#include "Map.h"
#include "Utils.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Block.h"

Map::Map(SDL_Renderer* renderer) : renderer(renderer), background_rect(), background_text(nullptr), border_text(nullptr) {
	map = std::vector<std::vector<int>>(SCREEN_ROW, std::vector<int>(SCREEN_COL, 0));
	background_text = TextureManager::loadTexture(renderer, "assets/background.png");
	border_text = TextureManager::loadTexture(renderer, "assets/border.png");

	block_textures[I_block - I_block] = TextureManager::loadTexture(renderer, "assets/I_block_tile.png");
	block_textures[J_block - I_block] = TextureManager::loadTexture(renderer, "assets/J_block_tile.png");
	block_textures[L_block - I_block] = TextureManager::loadTexture(renderer, "assets/L_block_tile.png");
	block_textures[O_block - I_block] = TextureManager::loadTexture(renderer, "assets/O_block_tile.png");
	block_textures[S_block - I_block] = TextureManager::loadTexture(renderer, "assets/S_block_tile.png");
	block_textures[T_block - I_block] = TextureManager::loadTexture(renderer, "assets/T_block_tile.png");
	block_textures[Z_block - I_block] = TextureManager::loadTexture(renderer, "assets/Z_block_tile.png");


	for (int i = 0; i < SCREEN_ROW; i++) {
		for (int j = 0; j < SCREEN_COL; j++) {
			if (i == SCREEN_ROW - 1 || j == 0 || j == SCREEN_COL - 1) {
				map[i][j] = 1;
			}
		}
	}

	background_rect.w = TILE_W;
	background_rect.h = TILE_H;
}

Map::~Map() {
	SDL_DestroyTexture(border_text);
	SDL_DestroyTexture(background_text);
	for (auto& text : block_textures) {
		SDL_DestroyTexture(text);
	}
}

bool Map::checkBottomCollision(const Block& block) {
	auto pair = block.calculateCornerCoordinates();
	int Cx{ pair.first };
	int Cy = { pair.second };

	auto& block_matrix = block.getBlock();
	for (int i = 0; i < block_matrix.size(); i++) {
		for (int j = 0; j < block_matrix.at(i).size(); j++) {
			if (block_matrix[i][j] == block_tile && Cy + i >= 0) {
				if (Cy + i > SCREEN_ROW - 2) return true;
				if (map[Cy + i][Cx + j] != background && map[Cy + i][Cx + j] != border) return true;	
			}
		}
	}
	
	return false;
}

bool Map::checkTopCollision(const Block& block) {
	auto pair = block.calculateCornerCoordinates();
	int Cx{ pair.first };
	int Cy = { pair.second };

	auto& block_matrix = block.getBlock();
	for (int i = 0; i < block_matrix.size(); i++) {
		for (int j = 0; j < block_matrix.at(i).size(); j++) {
			if (block_matrix[i][j] == block_tile && Cy + i < 0) {
				return true;
			}
		}
	}

	return false;
}

void Map::placeBlock(const Block& block) {
	auto pair = block.calculateCornerCoordinates();
	int Cx{ pair.first };
	int Cy = { pair.second };

	auto& block_matrix = block.getBlock();
	for (int i = 0; i < block_matrix.size(); i++) {
		for (int j = 0; j < block_matrix.at(i).size(); j++) {
			if (block_matrix[i][j] == block_tile) {
				map[Cy + i][Cx + j] = block.getBlockID();
			}
		}
	}

}

void Map::render() {
	int type{};

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			type = map[i][j];

			background_rect.x = j * TILE_W;
			background_rect.y = i * TILE_H;
		
			switch (type) {

			case background:
				TextureManager::renderTexture(renderer, background_text, nullptr, &background_rect);
				break;

			case border:
				TextureManager::renderTexture(renderer, border_text, nullptr, &background_rect);
				break;
			
			case I_block:
			case J_block:
			case L_block:
			case O_block:
			case S_block:
			case T_block:
			case Z_block:
				TextureManager::renderTexture(renderer, block_textures[type - I_block], nullptr, &background_rect);
				break;
			}
		}
	}
}
