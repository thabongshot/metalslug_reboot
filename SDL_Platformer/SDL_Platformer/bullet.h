#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>
#include <iostream>

class Bullet {
private:
	SDL_Rect box;
	int xvel, yvel;
	SDL_Surface *image;
	void *owner;
	bool active;

public:
	Bullet(SDL_Surface *img, int x, int y, int xvel, int yvel, void *owner);

	SDL_Rect *getRect();

	void move();

	void *getOwner();

	void toggleActive(bool active);

	bool isActive();

	void show(SDL_Surface *screen, SDL_Rect *camera);
};

#endif