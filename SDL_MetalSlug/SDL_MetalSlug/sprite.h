#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "animation.h"

#include <vector>

#include <Box2D\Box2D.h>

class Sprite {
public:
	int xDir, yDir;
	bool moving;
	bool jumping;
	int moveSpeed;
	bool active;

	b2Body *body;

	std::vector<Animation*> animations;
	Animation *currAnimation;

	Sprite(int x, int y, int hw, int hh, int moveSpeed, std::vector<Animation*> animations);

	int getX();

	int getY();

	void SetCurrAnimation(int idx);

	Animation *getAnimation(int idx);

	virtual void Input(SDL_Event *e);

	virtual void Update(Timer *timer);

	virtual void Render(SDL_Renderer *renderer, int camX, int camY);
};

#endif