#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SDL.h>

#include "base.h"

class Game {
private:
	SDL_Surface *screen;
	SDL_Rect camera;
	std::vector<std::vector<SDL_Surface*>> map;
	bool direction[2];

	SDL_Surface *load_image(const char* fileName);
	void loadMap(const char* fileName);
	void showMap();
	void handleEvents();
	bool running;

	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

public:
	Game();
	~Game();

	void start();
};

#endif