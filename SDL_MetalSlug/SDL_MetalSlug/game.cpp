#include "game.h"

SDL_Rect BaseClass::coord;

SDL_Surface *background;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

	BaseClass::coord.x = BaseClass::coord.y = camera.x = camera.y = 0;
	BaseClass::coord.w = camera.w = SCREEN_WIDTH;
	BaseClass::coord.h = camera.h = SCREEN_HEIGHT;

	direction[0] = direction[1] = 0;
	running = true;

	background = load_image("test_background.bmp");
}

Game::~Game() {
	SDL_Quit();
}

SDL_Surface *Game::load_image(const char *fileName) {
	SDL_Surface *tmp = SDL_LoadBMP(fileName);
	SDL_Surface *tmp2 = SDL_DisplayFormat(tmp);
	//SDL_SetColorKey(tmp2, SDL_SRCCOLORKEY, SDL_MapRGB(screen->format, 0x00, 0xff, 0xff));
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

}

void Game::start() {
	Uint32 start;
	loadMap("mapFile");
	while(running) {
		start = SDL_GetTicks();
		handleEvents();

		if(direction[0]) {
			camera.x--;
			BaseClass::coord.x--;
			if(camera.x < 0) {
				camera.x = 0;
			}
		}
		if(direction[1]) {
			camera.x++;
			BaseClass::coord.x++;
			if(camera.x > 1000 - SCREEN_WIDTH) {
				camera.x = 1000 - SCREEN_WIDTH;
			}
		}

		// Blit Background Surface
		SDL_BlitSurface(background, &camera, screen, NULL);
		showMap();

		SDL_Flip(screen);
		if(1000 / 30 > (SDL_GetTicks() - start)) {
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - start));
		}
	}
}