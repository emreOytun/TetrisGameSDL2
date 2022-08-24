#include "Block.h"
#include "Utils.h"

Block::Block(SDL_Renderer* renderer, int block_id) : block_id(block_id), x0(), y0(-1), speed(1), state(horizantal), text(nullptr) {
	x0 = ((double)SCREEN_COL - 1) / 2;
	
	block = std::vector<std::vector<int>>(2, std::vector<int>(4, empty));
	
	/* BLOKLARIN ICINI DOLDUR VE ASSETLERI EKLE. */
	switch (block_id) {
	case I_block:
		block[1][0] = block[1][1] = block[1][2] = block[1][3] = block_tile;
	
		text = TextureManager::loadTexture(renderer, "assets/I_block_tile.png");
		break;

	case J_block:
		block[0][2] = block[1][2] = block[1][1] = block[1][0] = block_tile;
			
		text = TextureManager::loadTexture(renderer, "assets/J_block_tile.png");
		break;

	case L_block:
		block[0][1] = block[1][1] = block[1][2] = block[1][3] = block_tile;

		text = TextureManager::loadTexture(renderer, "assets/L_block_tile.png");
		break;

	case O_block:
		block[0][1] = block[0][2] = block[1][1] = block[1][2] = block_tile;

		text = TextureManager::loadTexture(renderer, "assets/O_block_tile.png");
		break;

	case S_block:
		block[0][3] = block[0][2] = block[1][2] = block[1][1] = block_tile;

		text = TextureManager::loadTexture(renderer, "assets/S_block_tile.png");
		break;

	case T_block:
		block[0][1] = block[1][0] = block[1][1] = block[1][2] = block_tile;

		text = TextureManager::loadTexture(renderer, "assets/T_block_tile.png");
		break;
		
	case Z_block:
		block[0][0] = block[0][1] = block[1][1] = block[1][2] = block_tile;

		text = TextureManager::loadTexture(renderer, "assets/Z_block_tile.png");
		break;

	default:
		break;
	}


	blockRect.w = TILE_W;
	blockRect.h = TILE_H;
}

Block::~Block() {
	SDL_DestroyTexture(text);
}

std::pair<int, int> Block::calculateCornerCoordinates() const {
	int Cx{}, Cy{};
	switch (state) {

	case horizantal:
		Cx = (int)(x0 - 2);
		Cy = (int)(y0 - 1);
		break;

	case vertical:
		Cx = (int)(x0 - 1);
		Cy = (int)(y0 - 2);
		break;
	}

	return std::make_pair(Cx, Cy);
}

const std::vector<std::vector<int>>& Block::getBlock() const {
	return block;
}

int Block::getBlockID() const {
	return block_id;
}

void Block::setSpeed(int s) {
	speed = s;
}

bool Block::checkHorizantolCollision() const {
	auto pair = calculateCornerCoordinates();
	int Cx = pair.first;
	int Cy = pair.second;

	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == block_tile) {
				if (Cx + j > SCREEN_COL - 2 || Cx + j < 1) return true;
			}
		}
	}
	
	return false;
}

void Block::moveHorizantal(int direction) {

	switch (direction) {
	case left:
		--x0;
		if (checkHorizantolCollision()) ++x0;
		break;

	case right :
		++x0;
		if (checkHorizantolCollision()) --x0;
		break;
	}		
}

void Block::rotate() {
	do {
		std::vector<std::vector<int>> rotated_block(block[0].size(), std::vector<int>(block.size(), 0));

		for (int i = 0; i < block.size(); i++) {
			for (int j = 0; j < block[i].size(); j++) {
				rotated_block[j][block.size() - 1 - i] = block[i][j];
			}
		}

		block = rotated_block;

	} while (checkHorizantolCollision() == true);
}

void Block::back_one_step() {
	y0--;
}

void Block::update() {
	y0 += speed;
}

void Block::render(SDL_Renderer* renderer) {
	auto pair = calculateCornerCoordinates();
	int Cx = pair.first;
	int Cy = pair.second;

	/*
	std::cout << "x0,y0:" << "(" << x0 << "," << y0 << ")" << std::endl;
	std::cout << "Cx,Cy:" << "(" << Cx << "," << Cy << ")" << std::endl;
	*/

	for (int i = 0; i < block.size(); i++) {
		for (int j = 0; j < block[i].size(); j++) {
			if (block[i][j] == block_tile) {
				blockRect.x = (Cx + j) * TILE_W;
				blockRect.y = (Cy + i) * TILE_H;
				TextureManager::renderTexture(renderer, text, nullptr, &blockRect);
			}
		}
	}	
}

std::vector<int> Block::operator[](int pos) const {
	
	if (pos < 0 || pos > block.size() - 1) {
		throw std::invalid_argument("Out of boundary !");
	}
	
	return block[pos];
}

