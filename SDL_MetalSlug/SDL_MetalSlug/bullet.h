#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>
#include <iostream>

class Bullet {
private:
	SDL_Rect box;
	int xvel, yvel;
	SDL_Surface *image;

public:
	Bullet(SDL_Surface *img, int x, int y, int xvel, int yvel);

	SDL_Rect *getRect();

	void move();

	void show(SDL_Surface *screen);
};

#endif