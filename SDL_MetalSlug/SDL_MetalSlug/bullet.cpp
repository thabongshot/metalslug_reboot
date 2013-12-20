#include "bullet.h"

#include "base.h"

Bullet::Bullet(SDL_Surface *image, int x, int y, int xvel, int yvel, void *owner) {
	box.x = x;
	box.y = y;
	this->image = image;

	box.w = image->w;
	box.h = image->h;

	this->xvel = xvel;
	this->yvel = yvel;

	this->owner = owner;
	active = true;
}

SDL_Rect *Bullet::getRect() {
	return &box;
}

void Bullet::move() {
	box.x += xvel;
	box.y += yvel;
}

void *Bullet::getOwner() {
	return owner;
}

void Bullet::toggleActive(bool active) {
	this->active = active;
}

bool Bullet::isActive() {
	return active;
}

void Bullet::show(SDL_Surface *screen, SDL_Rect *camera) {
	SDL_Rect tmpRect;
	tmpRect.x = box.x - camera->x;
	tmpRect.y = box.y - camera->y;
	tmpRect.w = box.w;
	tmpRect.h = box.h;

	SDL_BlitSurface(image, NULL, screen, &tmpRect);
}