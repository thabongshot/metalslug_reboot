#ifndef _SCENE_H_
#define _SCENE_H_

#include "timer.h"
#include "sprite.h"
#include <vector>

#include <SDL.h>
#include <SDL_events.h>

class Scene {
public:
	std::vector<Sprite*> sprites;

	Scene();

	virtual void Init(SDL_Renderer *renderer);

	virtual void Dispose();

	virtual void Input(SDL_Event *e);

	virtual void Update(Timer *timer);

	virtual void Render(SDL_Renderer *renderer);
};

#endif