#ifndef _TESTSCENE_H_
#define _TESTSCENE_H_

#include "scene.h"

class TestScene : public Scene {
public:
	TestScene();

	virtual void Init(SDL_Renderer *renderer);

	virtual void Dispose();

	virtual void Input(SDL_Event *e);

	virtual void Update(Timer *timer);

	virtual void Render(SDL_Renderer *renderer);
};

#endif