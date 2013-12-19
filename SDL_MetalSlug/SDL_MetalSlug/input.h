#ifndef _INPUT_H_
#define _INPUT_H_

#include <SDL.h>

class Input {
private:
	static bool *keys;

public:
	Input();

	static void Update(SDL_Event *e);

	static bool isKeyPressed(int key);
};

#endif