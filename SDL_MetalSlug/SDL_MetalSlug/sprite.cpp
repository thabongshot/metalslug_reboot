#include "sprite.h"

#include "level.h"

Sprite::Sprite(int x, int y, int hw, int hh, int moveSpeed, std::vector<Animation*> animations) {
	this->moveSpeed = moveSpeed;
	this->animations = animations;
	this->currAnimation = nullptr;
	this->active = true;

	xDir = 0;
	yDir = 0;

	b2BodyDef *bodyDef = new b2BodyDef();
	bodyDef->fixedRotation = true;
	bodyDef->type = b2_dynamicBody;

	b2Shape *shape = new b2PolygonShape();
	((b2PolygonShape*)shape)->SetAsBox(hw, hh, b2Vec2(0.5f, 0.5f), 0);

	b2FixtureDef *fixtureDef = new b2FixtureDef();
	fixtureDef->density = 1.0f;
	fixtureDef->shape = shape;

	body = Level::world->CreateBody(bodyDef);
	body->CreateFixture(fixtureDef);

	body->SetTransform(b2Vec2(x, y), 0);
}

int Sprite::getX() {
	return body->GetPosition().x;
}

int Sprite::getY() {
	return body->GetPosition().y;
}

void Sprite::SetCurrAnimation(int idx) {
	if(idx >= 0 && idx < animations.size()) {
		if(currAnimation) {
			currAnimation->played = false;
			currAnimation->finished = true;
		}
		currAnimation = animations[idx];
		currAnimation->played = true;
		currAnimation->finished = false;
	}
}

Animation *Sprite::getAnimation(int idx) {
	if(idx >= 0 && idx < animations.size()) {
		return animations[idx];
	}
	
	return nullptr;
}

void Sprite::Input(SDL_Event *e) {

}

void Sprite::Update(Timer *timer) {
	if(!active) return;

	if(currAnimation)
		currAnimation->Update(timer);
}

void Sprite::Render(SDL_Renderer *renderer, int camX, int camY) {
	if(!active) return;

	if(currAnimation)
		currAnimation->Render(body->GetPosition().x, body->GetPosition().y, camX, camY, renderer);
}