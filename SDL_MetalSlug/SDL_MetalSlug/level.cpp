#include "level.h"

Level::Level(LevelLayer *back1, LevelLayer *back2, LevelLayer *actor, LevelLayer *fore) {
	this->background1 = back1;
	this->background2 = back2;
	this->actor = actor;
	this->foreground = fore;
}

void Level::Input(SDL_Event *e) {
	if(actor)
		actor->Input(e);
}

void Level::Update(Timer *timer) {
	if(background1)
		background1->Update(timer);
	if(background2)
		background2->Update(timer);
	if(actor)
		actor->Update(timer);
	if(foreground)
		foreground->Update(timer);
}

void Level::Render(SDL_Renderer *renderer, int camX, int camY) {
	if(background1)
		background1->Render(renderer, camX, camY);
	if(background2)
		background2->Render(renderer, camX, camY);
	if(actor)
		actor->Render(renderer, camX, camY);
	if(foreground)
		foreground->Render(renderer, camX, camY);
}