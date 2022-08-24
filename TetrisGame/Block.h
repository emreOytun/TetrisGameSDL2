#pragma once
#include <vector>
#include <iostream>
#include <SDL.h>

class Block
{
private :
	double x0, y0;
	int state;
	int speed;
	
	int block_id;
	std::vector<std::vector<int>> block;
	SDL_Texture* text;
	SDL_Rect blockRect;


public :
	Block(SDL_Renderer* renderer, int block_id);
	~Block();
	std::pair<int, int> calculateCornerCoordinates() const;
	
	const std::vector<std::vector<int>>& getBlock() const;
	int getBlockID() const;
	void setSpeed(int s);

	bool checkHorizantolCollision() const;
	void moveHorizantal(int direction);
	
	void rotate();

	void back_one_step();
	void update();
	void render(SDL_Renderer *renderer);

	std::vector<int> operator[](int pos) const;

};

