#include "game.h"
#include "pixel.h"

SDL_Rect BaseClass::coord;
SDL_Rect BaseClass::window_coord;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
	canvas = SDL_DisplayFormat(screen);
	SDL_ShowCursor(0);

	BaseClass::coord.x = BaseClass::coord.y = camera.x = camera.y = 0;
	BaseClass::coord.w = camera.w = BACKBUFFER_WIDTH;
	BaseClass::coord.h = camera.h = BACKBUFFER_HEIGHT;

	BaseClass::window_coord.x = BaseClass::window_coord.y = 0;
	BaseClass::window_coord.w = SCREEN_WIDTH;
	BaseClass::window_coord.h = SCREEN_HEIGHT;

	direction[0] = direction[1] = 0;
	last_direction = 1;
	running = true;

	player1 = new Player(load_image("player.bmp"));
	player1->getRect()->y = 100;

	entities.push_back(new Player(load_image("enemy.bmp")));
	entities.back()->getRect()->x = 500;
	entities.back()->getRect()->y = 100;

	entities.push_back(new Player(load_image("enemy.bmp")));
	entities.back()->getRect()->x = 600;
	entities.back()->getRect()->y = 100;

	bulletImg = load_image("bullet.bmp");

	building_corridor = load_image("building_corridor.bmp");
	building_corridor_rect.x = 0;
	building_corridor_rect.y = 0;
	building_corridor_rect.w = building_corridor->w;
	building_corridor_rect.h = building_corridor->h;

	building_corridor_wall = load_image("building_corridor_wall.bmp");
	building_corridor_wall_rect.x = 0;
	building_corridor_wall_rect.y = 80;
	building_corridor_wall_rect.w = building_corridor_wall->w;
	building_corridor_wall_rect.h = building_corridor_wall->h;

	debris = load_image("debris.bmp");
	debris_rect.x = 0;
	debris_rect.y = 170;
	debris_rect.w = debris->w;
	debris_rect.h = debris->h;
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
				last_direction = 0;
				break;
			case SDLK_RIGHT:
				direction[1] = 1;
				last_direction = 1;
				break;
			case SDLK_a:
				if(last_direction == 0) {
					bullets.push_back(new Bullet(bulletImg, player1->getRect()->x - 20, player1->getRect()->y + 25, -bulletSpeed, 0));
				}
				else if(last_direction == 1) {
					bullets.push_back(new Bullet(bulletImg, player1->getRect()->x + player1->getRect()->w, player1->getRect()->y + 25, bulletSpeed, 0));
				}
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
	SDL_BlitSurface(building_corridor_wall, &camera, canvas, &building_corridor_wall_rect);
	SDL_BlitSurface(building_corridor, &camera, canvas, &building_corridor_rect);

	for(int i = 0; i < entities.size(); i++) {
		entities[i]->show(canvas, &camera);
	}

	player1->show(canvas, &camera);

	for(int i = 0; i < bullets.size(); i++) {
		bullets[i]->show(canvas, &camera);
	}

	SDL_BlitSurface(debris, &camera, canvas, &debris_rect);
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
				}
			}
			else player1->setXVel(0);
			if(camera.x < 0) {
				camera.x = 0;
			}
		}
		else if(direction[1]) {
			if(player1->getRect()->x < 2128 - player1->getRect()->w) {
				player1->setXVel(playerSpeed);
				if(player1->getRect()->x - camera.x >= BaseClass::coord.w / 2 - player1->getRect()->w / 2) {
					camera.x += playerSpeed;
				}
			}
			else player1->setXVel(0);
			if(camera.x > 2128 - camera.w) {
				camera.x = 2128 - camera.w;
			}
		}
		else {
			player1->setXVel(0);
		}

		for(int i = 0; i < bullets.size(); i++) {
			if(bullets[i]->getRect()->x + bullets[i]->getRect()->w + 10 >= camera.x + camera.w ||
				bullets[i]->getRect()->x + 15 <= camera.x) {
					delete bullets[i];
					bullets.erase(bullets.begin() + i);
			}
			else {
				for(int j = 0; j < entities.size(); j++) {
					if(entities[j]->collision(entities[j]->getRect(), bullets[i]->getRect())) {
						delete bullets[i];
						bullets.erase(bullets.begin() + i);
						delete entities[j];
						entities.erase(entities.begin() + j);
					}
				}
			}
		}

		player1->move(map);

		for(int i = 0; i < entities.size(); i++) {
			entities[i]->move(map);
		}

		for(int i = 0; i < bullets.size(); i++) {
			bullets[i]->move();
		}

		SDL_FillRect(canvas, &BaseClass::coord, NULL);

		showMap();

		SDL_SoftStretch(canvas, &BaseClass::coord, screen, &BaseClass::window_coord);

		SDL_Flip(screen);
		if(1000 / 30 > (SDL_GetTicks() - start)) {
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - start));
		}
	}
}