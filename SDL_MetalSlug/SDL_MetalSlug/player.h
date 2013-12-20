#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include "base.h"

class Player : public BaseClass{
protected:
	SDL_Rect box;
	std::vector<SDL_Surface*> sheets;
	std::vector<std::vector<SDL_Rect>> animClips;
	std::vector<bool> loop;
	int currAnim;
	int xvel, yvel;
	int hp;
	bool ground;
	bool jump;
	int lastDirection;
	double frame;

public:
	Player(std::vector<SDL_Surface*> sheets, 
		   std::vector<std::vector<SDL_Rect>> animClips,
		   std::vector<bool> loop,
		   int hp);
	~Player();

	SDL_Rect *getRect();

	void setXVel(int vel);
	int getXVel();

	void setYVel(int vel);
	int getYVel();

	void setHP(int hp);
	int getHP();

	int getLastDirection();
	void setLastDirection(int dir);

	void setCurrAnim(int idx);

	bool isJumping();
	bool isGrounded();

	void setGrounded();
	void setJump(int vel);

	void damage(int amount);

	void move(const std::vector<std::vector<int>> map);
	void show(SDL_Surface *screen, SDL_Rect *camera);
};

#endif