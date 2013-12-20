#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "base.h"

class Player : public BaseClass{
private:
	SDL_Rect box;
	SDL_Surface *image;
	int xvel, yvel;
	SDL_Rect clips[1];

public:
	Player(SDL_Surface *img);
	~Player();

	SDL_Rect *getRect();

	void setXVel(int vel);
	int getXVel();

	void setYVel(int vel);
	int getYVel();

	void move(const std::vector<std::vector<int>> map);
	void show(SDL_Surface *screen, SDL_Rect *camera);
};

#endif