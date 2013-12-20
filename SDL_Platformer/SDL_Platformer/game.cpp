#include "game.h"

#include "util.h"

SDL_Rect BaseClass::coord;
SDL_Rect BaseClass::window_coord;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
	canvas = SDL_DisplayFormat(screen);
	//SDL_ShowCursor(0);

	BaseClass::coord.x = BaseClass::coord.y = camera.x = camera.y = 0;
	BaseClass::coord.w = camera.w = BACKBUFFER_WIDTH;
	BaseClass::coord.h = camera.h = BACKBUFFER_HEIGHT;

	BaseClass::window_coord.x = BaseClass::window_coord.y = 0;
	BaseClass::window_coord.w = SCREEN_WIDTH;
	BaseClass::window_coord.h = SCREEN_HEIGHT;

	direction[0] = direction[1] = 0;
	running = true;

	createEri(50, 150);

	createPtolemaicSoldier(300, 150);
	createPtolemaicSoldier(360, 150);
	createPtolemaicSoldier(700, 150);
	createPtolemaicSoldier(770, 150);
	createPtolemaicSoldier(800, 150);
	createPtolemaicSoldier(1000, 150);
	createPtolemaicSoldier(1050, 150);
	createPtolemaicSoldier(1500, 150);

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
	debris_rect.y = 175;
	debris_rect.w = debris->w;
	debris_rect.h = debris->h;

	loadMap("out.xml");
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
			if(!player1 || !player1->isAlive()) {
				direction[0] = 0;
				direction[1] = 0;
				break;
			}
			switch(e.key.keysym.sym) {
			case SDLK_LEFT:
				direction[0] = 1;
				if(player1->isGrounded()) {
					player1->setLastDirection(-1);
					player1->setCurrAnim(3);
				}
				break;
			case SDLK_RIGHT:
				direction[1] = 1;
				if(player1->isGrounded()) {
					player1->setLastDirection(1);
					player1->setCurrAnim(2);
				}
				break;
			case SDLK_a:
				if(player1->getLastDirection() == -1) {
					bullets.push_back(new Bullet(bulletImg, player1->getRect()->x - 5, player1->getRect()->y + 10, -bulletSpeed, 0, player1));
				}
				else if(player1->getLastDirection() == 1) {
					bullets.push_back(new Bullet(bulletImg, player1->getRect()->x + player1->getRect()->w - 10, player1->getRect()->y + 10, bulletSpeed, 0, player1));
				}
				break;
			case SDLK_s:
				if(player1->isGrounded()) {
					if(direction[0] == 0 && direction[1] == 0) {
					if(player1->getLastDirection() == -1)
						player1->setCurrAnim(5);
					else if(player1->getLastDirection() == 1)
						player1->setCurrAnim(4);
				}
					else if(direction[0] == 1)
						player1->setCurrAnim(7);
					else if(direction[1] == 1)
						player1->setCurrAnim(6);
				}
				player1->setJump(-12);
				break;
			}
			break;
		case SDL_KEYUP:
			if(!player1 || !player1->isAlive()) {
				direction[0] = 0;
				direction[1] = 0;
				break;
			}
			switch(e.key.keysym.sym) {
			case SDLK_LEFT:
				direction[0] = 0;
				if(player1->getLastDirection() == -1) {
					if(player1->isGrounded())
						player1->setCurrAnim(1);
				}
				break;
			case SDLK_RIGHT:
				direction[1] = 0;
				if(player1->getLastDirection() == 1) {
					if(player1->isGrounded())
						player1->setCurrAnim(0);
				}
				break;
			}
			break;
		}
	}
}

void Game::loadMap(const char *fileName) {
	MapData *mData = new MapData();

	ParseMapData(fileName, mData);

	for(int i = 0; i < mData->mImageResourceList.size(); i++) {
		std::cout << mData->mImageResourceList[i]->imgsrc << std::endl;
	}
}

void Game::showMap() {
	SDL_BlitSurface(building_corridor_wall, &camera, canvas, &building_corridor_wall_rect);
	SDL_BlitSurface(building_corridor, &camera, canvas, &building_corridor_rect);

	for(int i = 0; i < entities.size(); i++) {
		entities[i]->show(canvas, &camera);
	}

	if(player1)
		player1->show(canvas, &camera);

	for(int i = 0; i < bullets.size(); i++) {
		bullets[i]->show(canvas, &camera);
	}
	
	for(int i = 0; i <= 2128 / debris->w; i++) {
		debris_rect.x = i * debris->w - camera.x;
		SDL_BlitSurface(debris, NULL, canvas, &debris_rect);
	}
	
}

void Game::start() {
	Uint32 start;
	while(running) {
		start = SDL_GetTicks();
		handleEvents();

		update();

		show();

		SDL_Flip(screen);
		if(1000 / 30 > (SDL_GetTicks() - start)) {
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - start));
		}
	}
}

void Game::update() {
	if(player1)
		movePlayer();

	moveBullets();

	for(int i = 0; i < entities.size(); i++) {
		if(player1) {
			int distance = entities[i]->calculateDistance(entities[i]->getRect(), player1->getRect());
			if(distance < 6400 && distance > 400) {
				entities[i]->alarm(player1);
			}
			else if(distance < 400) {
				entities[i]->ceaseAlarm();
				entities[i]->setXVel(0);
				// Attack!
				player1->damage(1);
				if(player1->getHP() == 0) {
					player1->killIdle(entities[i]->getRect()->x >= player1->getRect()->x ? 1 : -1);
				}
			}
			else entities[i]->ceaseAlarm();
		}

		entities[i]->move(map);
		if(entities[i]->getRect()->y + entities[i]->getRect()->h >= 190) {
			entities[i]->setGrounded();
			entities[i]->getRect()->y = 190 - entities[i]->getRect()->h;
		}
	}

	if(player1 && !player1->isAlive() && player1->isCurrAnimFinished()) {
		delete player1;
		player1 = nullptr;

		createEri(50, 150);
	}
}

void Game::movePlayer() {
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

	player1->move(map);
	
	if(player1->getRect()->y + player1->getRect()->h >= 190) {
		if(!player1->isGrounded()) {
			if(direction[0] == 1) {
				player1->setLastDirection(-1);
				player1->setCurrAnim(3);
			}
			else if(direction[1] == 1) {
				player1->setLastDirection(1);
				player1->setCurrAnim(2);
			}
			else {
				if(player1->getLastDirection() == -1) {
					player1->setCurrAnim(1);
				}
				else if(player1->getLastDirection() == 1) {
					player1->setCurrAnim(0);
				}
			}
		}

		player1->setGrounded();
		player1->getRect()->y = 190 - player1->getRect()->h;
	}
	
}

void Game::moveBullets() {
	for(int i = 0; i < bullets.size(); i++) {
		if(bullets[i]->getRect()->x + bullets[i]->getRect()->w + 10 >= camera.x + camera.w ||
			bullets[i]->getRect()->x + 15 <= camera.x) {
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
		}
		else if(bullets[i]->isActive()){
			for(int j = 0; j < entities.size(); j++) {
				if(bullets[i]->getOwner() != entities[j] && entities[j]->collision(entities[j]->getRect(), bullets[i]->getRect())) {
					entities[j]->damage(1);

					if(entities[j]->getHP() == 0) {
						delete entities[j];
						entities.erase(entities.begin() + j);
					}

					bullets[i]->toggleActive(false);
				}
			}
		}
	}

	for(int i = 0; i < bullets.size(); i++) {
		if(!bullets[i]->isActive()) {
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
		}
	}

	for(int i = 0; i < bullets.size(); i++) {
		bullets[i]->move();
	}
}

void Game::show() {
	SDL_FillRect(canvas, &BaseClass::coord, NULL);

	showMap();

	SDL_SoftStretch(canvas, &BaseClass::coord, screen, &BaseClass::window_coord);
}

void Game::createEri(int x, int y) {
	std::vector<SDL_Surface*> animations;
	std::vector<std::vector<SDL_Rect>> animClips;
	std::vector<bool> loop;
	std::vector<double> animSpeed;
	
	animations.push_back(load_image("eri_idle.bmp"));
	animations.push_back(load_image("eri_idle_left.bmp"));
	animations.push_back(load_image("eri_run.bmp"));
	animations.push_back(load_image("eri_run_left.bmp"));
	animations.push_back(load_image("eri_stop_jump.bmp"));
	animations.push_back(load_image("eri_stop_jump_left.bmp"));
	animations.push_back(load_image("eri_run_jump.bmp"));
	animations.push_back(load_image("eri_run_jump_left.bmp"));
	animations.push_back(load_image("eri_die_idle.bmp"));
	animations.push_back(load_image("eri_die_idle_left.bmp"));

	std::vector<SDL_Rect> idleClips;
	for(int i = 0; i < 4; i++) {
		SDL_Rect tmp;
		tmp.x = i * 32;
		tmp.y = 0;
		tmp.w = 32;
		tmp.h = 38;
		idleClips.push_back(tmp);
	}
	animClips.push_back(idleClips);
	animClips.push_back(idleClips);
	loop.push_back(true);
	loop.push_back(true);
	animSpeed.push_back(0.2);
	animSpeed.push_back(0.2);

	std::vector<SDL_Rect> runClips;
	for(int i = 0; i < 12; i++) {
		SDL_Rect tmp;
		tmp.x = i * 32;
		tmp.y = 0;
		tmp.w = 32;
		tmp.h = 42;
		runClips.push_back(tmp);
	}
	animClips.push_back(runClips);
	animClips.push_back(runClips);
	loop.push_back(true);
	loop.push_back(true);
	animSpeed.push_back(0.6);
	animSpeed.push_back(0.6);

	std::vector<SDL_Rect> stopJumpClips;
	for(int i = 0; i < 10; i++) {
		SDL_Rect tmp;
		tmp.x = i * 32;
		tmp.y = 0;
		tmp.w = 32;
		tmp.h = 48;
		stopJumpClips.push_back(tmp);
	}
	animClips.push_back(stopJumpClips);
	animClips.push_back(stopJumpClips);
	loop.push_back(false);
	loop.push_back(false);
	animSpeed.push_back(0.2);
	animSpeed.push_back(0.2);

	std::vector<SDL_Rect> runJumpClips;
	for(int i = 0; i < 6; i++) {
		SDL_Rect tmp;
		tmp.x = i * 32;
		tmp.y = 0;
		tmp.w = 32;
		tmp.h = 47;
		runJumpClips.push_back(tmp);
	}
	animClips.push_back(runJumpClips);
	animClips.push_back(runJumpClips);
	loop.push_back(false);
	loop.push_back(false);
	animSpeed.push_back(0.2);
	animSpeed.push_back(0.2);

	std::vector<SDL_Rect> dieIdleClips;
	for(int i = 0; i < 21; i++) {
		SDL_Rect tmp;
		tmp.x = i * 32;
		tmp.y = 0;
		tmp.w = 32;
		tmp.h = 39;
		dieIdleClips.push_back(tmp);
	}
	animClips.push_back(dieIdleClips);
	animClips.push_back(dieIdleClips);
	loop.push_back(false);
	loop.push_back(false);
	animSpeed.push_back(0.3);
	animSpeed.push_back(0.3);

	player1 = new Player(animations,
						 animClips,
						 loop,
						 animSpeed,
						 1);
	player1->getRect()->x = x;
	player1->getRect()->y = y;
	camera.x = 0;
	camera.y = 0;
}

void Game::createPtolemaicSoldier(int x, int y) {
	std::vector<SDL_Surface*> animations;
	std::vector<std::vector<SDL_Rect>> animClips;
	std::vector<bool> loop;
	std::vector<double> animSpeed;
	
	animations.push_back(load_image("ptolemaic_idle.bmp"));
	animations.push_back(load_image("ptolemaic_idle_left.bmp"));
	animations.push_back(load_image("ptolemaic_run.bmp"));
	animations.push_back(load_image("ptolemaic_run_left.bmp"));

	std::vector<SDL_Rect> idleClips;
	for(int i = 0; i < 8; i++) {
		SDL_Rect tmp;
		tmp.x = i * 32;
		tmp.y = 0;
		tmp.w = 32;
		tmp.h = 39;
		idleClips.push_back(tmp);
	}
	animClips.push_back(idleClips);
	animClips.push_back(idleClips);
	loop.push_back(true);
	loop.push_back(true);
	animSpeed.push_back(0.2);
	animSpeed.push_back(0.2);

	std::vector<SDL_Rect> runClips;
	for(int i = 0; i < 8; i++) {
		SDL_Rect tmp;
		tmp.x = i * 32;
		tmp.y = 0;
		tmp.w = 32;
		tmp.h = 37;
		runClips.push_back(tmp);
	}
	animClips.push_back(runClips);
	animClips.push_back(runClips);
	loop.push_back(true);
	loop.push_back(true);
	animSpeed.push_back(0.3);
	animSpeed.push_back(0.3);

	PtolemaicSoldier *enemy = new PtolemaicSoldier(animations,
												  animClips,
												  loop,
												  animSpeed,
												  5);
	enemy->getRect()->x = x;
	enemy->getRect()->y = y;

	entities.push_back(enemy);
}