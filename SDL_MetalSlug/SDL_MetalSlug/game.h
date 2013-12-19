#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include <vector>
#include <SDL.h>

#include "base.h"
#include "player.h"

#include "point.h"
#include "bullet.h"

class Game {
private:
	SDL_Surface *screen;
	SDL_Rect camera;
	std::vector<std::vector<int>> map;
	std::vector<Bullet*> bullets;
	bool direction[2];

	static const int playerSpeed = 3;

	SDL_Surface *load_image(const char* fileName);
	void loadMap(const char* fileName);
	void showMap();
	void handleEvents();
	bool running;

	Player *player1;

	SDL_Surface *building_corridor;
	SDL_Rect building_corridor_rect;

	SDL_Surface *building_corridor_wall;
	SDL_Rect building_corridor_wall_rect;

	SDL_Surface *bulletImg;

	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

public:
	Game();
	~Game();

	void start();
};

#endif