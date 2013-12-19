#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "animation.h"

class Sprite {
public:
	int x, y;
	int xDir, yDir;
	bool moving;
	bool jumping;
	int moveSpeed;
	bool active;
	int totalAnimations;

	Animation **animations;
	Animation *currAnimation;

	Sprite(int x, int y, int moveSpeed, Animation **animations, int totalAnimations);

	void SetCurrAnimation(int idx);

	Animation *getAnimation(int idx);

	virtual void Input(SDL_Event *e);

	virtual void Update(Timer *timer);

	virtual void Render(SDL_Renderer *renderer, int camX, int camY);
};

#endif