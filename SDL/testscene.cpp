#include "testscene.h"

#include "utils.h"

#include "sprite.h"

TestScene::TestScene() : Scene() {

}

Sprite *player;

void TestScene::Init(SDL_Renderer *renderer) {
	Animation **playerAnimations = (Animation**)malloc(sizeof(Animation*) * 2);
	playerAnimations[0] = new Animation(loadTextureExt(renderer, "car_idle.png"), 6, 1);
	playerAnimations[1] = new Animation(loadTextureExt(renderer, "car.png"), 8, 1);

	player = new Sprite(10, 270, 2, playerAnimations, 2);
	player->active = true;
	sprites.push_back(player);

	player->SetCurrAnimation(0);
}

void TestScene::Dispose() {
	
}

void TestScene::Input(SDL_Event *e) {
	if(e->type == SDL_MOUSEBUTTONDOWN) {
		
	}

	player->xDir = 0;
	player->yDir = 0;

	if(e->type == SDL_KEYDOWN) {
		switch(e->key.keysym.sym) {
		case SDLK_LEFT:
			player->xDir = -1;
			
			break;
		case SDLK_RIGHT:
			player->xDir = 1;
			
			break;
		case SDLK_UP:
			
			break;
		case SDLK_DOWN:
			
			break;
		case SDLK_SPACE:
			
			break;
		};
	}

	if(player->xDir != 0)
		player->SetCurrAnimation(1);
	else
		player->SetCurrAnimation(0);
}

void TestScene::Update(Timer *timer) {
	for(int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->Update(timer);
	}
}

void TestScene::Render(SDL_Renderer *renderer) {
	for(int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->Render(renderer);
	}
}