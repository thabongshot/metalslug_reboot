#include "level_layer.h"

LevelLayer::LevelLayer(Sprite **sprites, int totalSprites, int parallaxSpeed) {
	this->sprites = sprites;
	this->totalSprites = totalSprites;
	this->parallaxSpeed = parallaxSpeed;
}

void LevelLayer::Input(SDL_Event *e) {
	if(sprites) {
		for(int i = 0; i < totalSprites; i++) {
			sprites[i]->Input(e);
		}
	}
}

void LevelLayer::Update(Timer *timer) {
	if(sprites) {
		for(int i = 0; i < totalSprites; i++) {
			sprites[i]->Update(timer);
		}
	}
}

void LevelLayer::Render(SDL_Renderer *renderer, int camX, int camY) {
	if(sprites) {
		for(int i = 0; i < totalSprites; i++) {
			sprites[i]->Render(renderer, camX * parallaxSpeed, camY * parallaxSpeed);
		}
	}
}