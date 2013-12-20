#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <iostream>
#include <vector>
#include <SDL.h>

#include "base.h"
#include "player.h"
#include "bullet.h"

class Game {
private:
	SDL_Surface *screen;
	SDL_Surface *canvas;
	SDL_Rect camera;
	std::vector<std::vector<int>> map;
	std::vector<Bullet*> bullets;
	std::vector<Player*> entities;
	bool direction[2];

	static const int playerSpeed = 2;
	static const int bulletSpeed = 10;

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

	SDL_Surface *debris;
	SDL_Rect debris_rect;

	SDL_Surface *bulletImg;

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	static const int BACKBUFFER_WIDTH = 255;
	static const int BACKBUFFER_HEIGHT = 224;

public:
	Game();
	~Game();

	void createEri(int x, int y);

	void createEnemy(int x, int y);

	void start();

	void update();

	void movePlayer();

	void moveBullets();

	void show();
};

#endif