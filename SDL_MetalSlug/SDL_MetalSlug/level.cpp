#include "level.h"

b2World *Level::world;

Level::Level(LevelLayer *back1, LevelLayer *back2, LevelLayer *actor, LevelLayer *fore) {
	this->background1 = back1;
	this->background2 = back2;
	this->actor = actor;
	this->foreground = fore;

	world = new b2World(b2Vec2(0, GRAVITY_Y));
}

void Level::Input(SDL_Event *e) {
	if(actor)
		actor->Input(e);
}

void Level::Update(Timer *timer) {
	world->Step(1.0f / 60.0f, 8, 3);

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