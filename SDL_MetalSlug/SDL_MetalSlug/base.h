#ifndef BASE_H
#define BASE_H

#include <SDL.h>

#include <vector>
#include "point.h"

class BaseClass {
protected:
	bool collision(SDL_Rect *rect1, SDL_Rect *rect2);

public:
	static SDL_Rect coord;
	static const int TILE_SIZE = 50;
};

#endif