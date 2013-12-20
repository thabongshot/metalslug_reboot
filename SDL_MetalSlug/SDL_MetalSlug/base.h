#ifndef BASE_H
#define BASE_H

#include <SDL.h>

#include <vector>

class BaseClass {
public:
	static SDL_Rect coord;
	static SDL_Rect window_coord;
	static const int TILE_SIZE = 50;

	bool collision(SDL_Rect *rect1, SDL_Rect *rect2);
};

#endif