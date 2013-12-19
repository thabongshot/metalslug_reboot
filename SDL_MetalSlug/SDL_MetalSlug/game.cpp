#include "game.h"

SDL_Rect BaseClass::coord;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

	BaseClass::coord.x = BaseClass::coord.y = camera.x = camera.y = 0;
	BaseClass::coord.w = camera.w = SCREEN_WIDTH;
	BaseClass::coord.h = camera.h = SCREEN_HEIGHT;

	direction[0] = direction[1] = 0;
	running = true;

	player1 = new Player(load_image("player.bmp"));
	player1->getRect()->y = 100;

	bulletImg = load_image("bullet.bmp");

	building_corridor = load_image("building_corridor.bmp");
	building_corridor_rect.x = 0;
	building_corridor_rect.y = 0;
	building_corridor_rect.w = 2128;
	building_corridor_rect.h = 216;

	building_corridor_wall = load_image("building_corridor_wall.bmp");
	building_corridor_wall_rect.x = 0;
	building_corridor_wall_rect.y = 80;
	building_corridor_wall_rect.w = 2128;
	building_corridor_wall_rect.h = 80;
}

Game::~Game() {
	delete player1;
	SDL_FreeSurface(building_corridor);
	SDL_FreeSurface(bulletImg);
	for(int i = 0; i < bullets.size(); i++) {
		delete bullets[i];
	}
	SDL_Quit();
}

SDL_Surface *Game::load_image(const char *fileName) {
	SDL_Surface *tmp = SDL_LoadBMP(fileName);
	SDL_Surface *tmp2 = SDL_DisplayFormat(tmp);
	SDL_SetColorKey(tmp2, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0xff, 0x00, 0xff));
	SDL_FreeSurface(tmp);

	return tmp2;
}

void Game::handleEvents() {
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type) {
		case SDL_QUIT:
			running = false;
			return;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym) {
			case SDLK_LEFT:
				direction[0] = 1;
				break;
			case SDLK_RIGHT:
				direction[1] = 1;
				break;
			case SDLK_a:
				bullets.push_back(new Bullet(bulletImg, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 15, 8, 0));
				break;
			}
			break;
		case SDL_KEYUP:
			switch(e.key.keysym.sym) {
			case SDLK_LEFT:
				direction[0] = 0;
				break;
			case SDLK_RIGHT:
				direction[1] = 0;
				break;
			}
			break;
		}
	}
}

void Game::loadMap(const char *fileName) {
	
}

void Game::showMap() {
	SDL_BlitSurface(building_corridor_wall, &camera, screen, &building_corridor_wall_rect);
	SDL_BlitSurface(building_corridor, &camera, screen, &building_corridor_rect);

	player1->show(screen);


}

void Game::start() {
	Uint32 start;
	while(running) {
		start = SDL_GetTicks();
		handleEvents();

		if(direction[0]) {
			if(player1->getRect()->x > 0) {
				player1->setXVel(-playerSpeed);
				if(player1->getRect()->x - camera.x <= BaseClass::coord.w / 2 - player1->getRect()->w / 2) {
					camera.x -= playerSpeed;
					BaseClass::coord.x -= playerSpeed;
				}
			}
			else player1->setXVel(0);
			if(camera.x < 0) {
				camera.x = 0;
				BaseClass::coord.x = 0;
			}
		}
		else if(direction[1]) {
			if(player1->getRect()->x < 2128 - player1->getRect()->w) {
				player1->setXVel(playerSpeed);
				if(player1->getRect()->x - camera.x >= BaseClass::coord.w / 2 - player1->getRect()->w / 2) {
					camera.x += playerSpeed;
					BaseClass::coord.x += playerSpeed;
				}
			}
			else player1->setXVel(0);
			if(camera.x > 2128 - SCREEN_WIDTH) {
				camera.x = 2128 - SCREEN_WIDTH;
				BaseClass::coord.x = 2128 - SCREEN_WIDTH;
			}
		}
		else {
			player1->setXVel(0);
		}

		for(int i = 0; i < bullets.size(); i++) {
			if(bullets[i]->getRect()->x >= BaseClass::coord.x + BaseClass::coord.w ||
				bullets[i]->getRect()->x + bullets[i]->getRect()->w <= BaseClass::coord.x) {
					delete bullets[i];
					bullets.erase(bullets.begin() + i);
			}
		}

		player1->move(map);

		for(int i = 0; i < bullets.size(); i++) {
			bullets[i]->move();
		}

		showMap();

		for(int i = 0; i < bullets.size(); i++) {
			bullets[i]->show(screen);
		}

		SDL_Flip(screen);
		if(1000 / 30 > (SDL_GetTicks() - start)) {
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - start));
		}
	}
}