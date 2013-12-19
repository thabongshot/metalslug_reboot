#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "timer.h"
#include "utils.h"

class Animation {
private:
	SDL_Texture *sheet;
	SDL_Rect *clips;
	int speed;
	int frames;
	int currFrame;

public:
	bool played;
	bool finished;
	int stateTime;

	Animation();

	Animation(SDL_Texture *sheet, int frames, int speed);
	
	void Update(Timer *timer);

	void Render(int x, int y, int camX, int camY, SDL_Renderer *renderer);
};

#endif