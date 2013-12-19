#ifndef _LEVEL_LAYER_
#define _LEVEL_LAYER_

#include "sprite.h"
#include "utils.h"
#include <SDL_events.h>

class LevelLayer {
public:
	std::vector<Sprite*> sprites;
	float parallaxSpeed;

	LevelLayer(float parallaxSpeed);

	void Input(SDL_Event *e);

	void Update(Timer *timer);

	void Render(SDL_Renderer *renderer, int camX, int camY);
};

#endif