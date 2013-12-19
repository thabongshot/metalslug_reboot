#include "level_layer.h"

LevelLayer::LevelLayer(float parallaxSpeed) {
	this->parallaxSpeed = parallaxSpeed;
}

void LevelLayer::Input(SDL_Event *e) {
	for(int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->Input(e);
	}
}

void LevelLayer::Update(Timer *timer) {
	for(int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->Update(timer);
	}
}

void LevelLayer::Render(SDL_Renderer *renderer, int camX, int camY) {
	for(int i = 0; i < sprites.size(); i++) {
		sprites.at(i)->Render(renderer, (int)((float)camX * parallaxSpeed), (int)((float)camY * parallaxSpeed));
	}
}