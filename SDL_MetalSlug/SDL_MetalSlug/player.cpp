#include "player.h"

Player::Player(SDL_Surface *img) {
	image = img;

	box.x = 0;
	box.y = 0;
	box.w = 50;
	box.h = 100;

	xvel = 0;
	yvel = 0;

	for(int i = 0; i < 1; i++) {
		clips[i].x = i * 50;
		clips[i].y = 0;
		clips[i].w = 50;
		clips[i].h = 100;
	}
}

Player::~Player() {
	SDL_FreeSurface(image);
}

SDL_Rect *Player::getRect() {
	return &box;
}

int Player::getXVel() {
	return xvel;
}

void Player::setXVel(int vel) {
	xvel = vel;
}

int Player::getYVel() {
	return yvel;
}

void Player::setYVel(int vel) {
	yvel = vel;
}

void Player::show(SDL_Surface *screen) {
	SDL_Rect tmpRect;
	tmpRect.x = box.x - BaseClass::coord.x;
	tmpRect.y = box.y - BaseClass::coord.y;
	tmpRect.w = box.w;
	tmpRect.h = box.h;

	SDL_BlitSurface(image, &clips[0], screen, &tmpRect);
}

void Player::move(const std::vector<std::vector<int>> map) {
	

	box.x += xvel;
	box.y += yvel;
}