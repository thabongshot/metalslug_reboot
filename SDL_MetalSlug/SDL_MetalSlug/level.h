#ifndef _LEVEL_H_
#define _LEVEL_H_

#define GRAVITY_Y 200

#include "level_layer.h"
#include "utils.h"

#include <SDL_events.h>

#include <Box2D\Box2D.h>

class Level {
private:
	LevelLayer *background1;
	LevelLayer *background2;
	LevelLayer *actor;
	LevelLayer *foreground;

public:
	static b2World *world;

	Level(LevelLayer *back1, LevelLayer *back2, LevelLayer *actor, LevelLayer *fore);

	void Input(SDL_Event *e);

	void Update(Timer *timer);

	void Render(SDL_Renderer *renderer, int camX, int camY);
};

#endif