#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include "window.h"
#include "timer.h"
#include "scene.h"

#include <SDL_events.h>

class Processor {
private:
	Window *windowPtr;
	Scene *scene;

	bool quit;

	void HandleEvents(SDL_Event *e);

	void Update(Timer *timer);

	void Render();

public:
	Processor(Window *window);

	SDL_Renderer *GetRenderer();

	void SetScene(Scene *scene);

	void Run();
};

#endif