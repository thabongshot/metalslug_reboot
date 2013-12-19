#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "sprite.h"

class Player : public Sprite {
public:
	Player(int x, int y, int hw, int hh, int moveSpeed, std::vector<Animation*> animations);

	virtual void Input(SDL_Event *e);

	virtual void Update(Timer *timer);

	virtual void Render(SDL_Renderer *renderer, int camX, int camY);
};

#endif