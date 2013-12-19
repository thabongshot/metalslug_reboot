#include "bullet.h"

#include "base.h"

Bullet::Bullet(SDL_Surface *image, int x, int y, int xvel, int yvel) {
	box.x = x;
	box.y = y;
	this->image = image;

	box.w = image->w;
	box.h = image->h;

	this->xvel = xvel;
	this->yvel = yvel;
}

SDL_Rect *Bullet::getRect() {
	return &box;
}

void Bullet::move() {
	box.x += xvel;
	box.y += yvel;
}

void Bullet::show(SDL_Surface *screen) {
	SDL_Rect tmpRect;
	tmpRect.x = box.x - BaseClass::coord.x;
	tmpRect.y = box.y - BaseClass::coord.y;
	tmpRect.w = box.w;
	tmpRect.h = box.h;

	SDL_BlitSurface(image, NULL, screen, &tmpRect);
}