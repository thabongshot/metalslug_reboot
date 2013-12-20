#include "player.h"

Player::Player(std::vector<SDL_Surface*> sheets, std::vector<std::vector<SDL_Rect>> animClips, std::vector<bool> loop, std::vector<double> animSpeed, int hp) {
	this->sheets = sheets;
	this->animClips = animClips;
	this->loop = loop;
	this->animSpeed = animSpeed;

	xvel = 0;
	yvel = 0;

	this->hp = hp;
	this->jump = 0;
	this->lastDirection = 1;

	setCurrAnim(0);

	alive = true;
}

Player::~Player() {
	
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

void Player::setHP(int hp) {
	this->hp = hp;
}

int Player::getHP() {
	return hp;
}

void Player::setLastDirection(int dir) {
	lastDirection = dir;
}

int Player::getLastDirection() {
	return lastDirection;
}

void Player::setJump(int vel) {
	if(!jump && ground) {
		jump = 1;
		ground = 0;
		yvel = vel;
		box.y -= 5;
	}
}

bool Player::isJumping() {
	return jump;
}

bool Player::isGrounded() {
	return ground;
}

void Player::setGrounded() {
	ground = 1;
}

void Player::damage(int amount) {
	hp -= amount;
	if(hp < 0) hp = 0;
}

void Player::setCurrAnim(int idx) {
	if(idx >= 0 && idx < sheets.size()) {
		currAnim = idx;
		frame = 0;
		box.w = animClips[currAnim][0].w;
		box.h = animClips[currAnim][0].h;
	}
}

bool Player::isCurrAnimFinished() {
	return ((int)frame == (animClips[currAnim].size() - 1));
}

void Player::show(SDL_Surface *screen, SDL_Rect *camera) {
	SDL_Rect tmpBodyRect;
	tmpBodyRect.x = box.x - camera->x;
	tmpBodyRect.y = box.y - camera->y;
	tmpBodyRect.w = box.w;
	tmpBodyRect.h = box.h;

	SDL_BlitSurface(sheets[currAnim], &animClips[currAnim][(int)frame], screen, &tmpBodyRect);
}

void Player::alarm(Player *target) {
	
}

void Player::ceaseAlarm() {

}

void Player::killIdle(int direction) {
	setXVel(0);
	setYVel(0);

	if(alive) {
		alive = false;

		if(direction == -1) {
			setCurrAnim(9);
		}
		else {
			setCurrAnim(8);
		}
	}
}

bool Player::isAlive() {
	return alive;
}

void Player::move(const std::vector<std::vector<int>> map) {
	if(!jump) {
		yvel = 5;
	}
	if(jump && yvel < 5) {
		yvel++;
	}
	else {
		jump = 0;
	}

	box.x += xvel;
	box.y += yvel;

	frame += animSpeed[currAnim];

	if((int)frame >= animClips[currAnim].size()) {
		if(loop[currAnim])
			frame = 0.0;
		else
			frame = animClips[currAnim].size() - 1;
	}
}