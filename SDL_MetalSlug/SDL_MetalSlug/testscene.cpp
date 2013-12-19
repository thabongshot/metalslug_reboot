#include "testscene.h"

#include "utils.h"

#include "player.h"
#include "camera.h"
#include "level.h"
#include "level_layer.h"

TestScene::TestScene() : Scene() {

}

Player *player;
Camera *camera;

Level *level;

LevelLayer *background1;
LevelLayer *background2;
LevelLayer *actor;
LevelLayer *foreground;

void TestScene::Init(SDL_Renderer *renderer) {
	camera = new Camera();

	background1 = new LevelLayer(0.8f);
	background2 = new LevelLayer(0.8f);
	actor = new LevelLayer(1.0f);
	foreground = new LevelLayer(1.2f);

	level = new Level(background1, background2, actor, foreground);

	std::vector<Animation*> anim;
	anim.push_back(new Animation(loadTextureExt(renderer, "blue_box.png"), 1, 1));

	std::vector<Animation*> ground;
	ground.push_back(new Animation(loadTextureExt(renderer, "red_box.png"), 1, 1));

	Sprite *groundSprite = new Sprite(0, 320, 32, 32, 0, ground);
	groundSprite->body->SetType(b2_staticBody);
	groundSprite->SetCurrAnimation(0);

	player = new Player(0, 0, 32, 32, 200, anim);
	player->SetCurrAnimation(0);

	actor->sprites.push_back(player);
	actor->sprites.push_back(groundSprite);
}

void TestScene::Dispose() {
	delete player;
	delete camera;
}

void TestScene::Input(SDL_Event *e) {
	level->Input(e);
}

void TestScene::Update(Timer *timer) {
	level->Update(timer);

	camera->x = player->getX();
	camera->y = player->getY();
}

void TestScene::Render(SDL_Renderer *renderer) {
	level->Render(renderer, camera->x, camera->y);
}