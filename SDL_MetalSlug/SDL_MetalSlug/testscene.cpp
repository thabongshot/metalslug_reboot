#include "testscene.h"

#include "utils.h"

#include "player.h"

TestScene::TestScene() : Scene() {

}

Player *player;

SDL_Texture **background;
int bW;
int b1x, b2x;

int camX, camY;

void TestScene::Init(SDL_Renderer *renderer) {
	Animation **playerAnimations = (Animation**)malloc(sizeof(Animation*) * 3);
	playerAnimations[0] = new Animation(loadTextureExt(renderer, "car_idle.png"), 6, 1);
	playerAnimations[1] = new Animation(loadTextureExt(renderer, "car.png"), 8, 1);
	playerAnimations[2] = new Animation(loadTextureExt(renderer, "car_jump.png"), 8, 1);

	background = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 2);

	background[0] = loadTextureExt(renderer, "mountain_background.png");
	background[1] = loadTextureExt(renderer, "mountain_background2.png");
	SDL_QueryTexture(background[0], NULL, NULL, &bW, NULL);

	b1x = 0;
	b2x = -bW;

	player = new Player(10, 270, 2, playerAnimations, 3);
	camX = 10;
	camY = 270;
	player->active = true;
	sprites.push_back(player);

	player->SetCurrAnimation(0);
}

void TestScene::Dispose() {
	
}

void TestScene::Input(SDL_Event *e) {
	for(int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->Input(e);
	}
}

void TestScene::Update(Timer *timer) {
	for(int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->Update(timer);
	}

	camX = player->x;
	camY = player->y;

	int idx = camX / bW;

	if(idx % 2 == 1) b1x = (2 * idx) * bW;
	if(idx % 2 == 0) b2x = (2 * idx + 1) * bW;
}

void TestScene::Render(SDL_Renderer *renderer) {
	ApplySurface(-camX + b1x, -camY + 260, background[0], renderer, NULL);
	ApplySurface(-camX + b2x, -camY + 260, background[1], renderer, NULL);

	for(int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->Render(renderer, camX, camY);
	}
}