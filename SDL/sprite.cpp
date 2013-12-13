#include "sprite.h"

Sprite::Sprite(int x, int y, int moveSpeed, Animation **animations, int totalAnimations) {
	this->x = x;
	this->y = y;
	this->moveSpeed = moveSpeed;
	this->animations = (Animation**)malloc(sizeof(Animation*) * totalAnimations);
	for(int i = 0; i < totalAnimations; i++) {
		this->animations[i] = animations[i];
	}
	this->totalAnimations = totalAnimations;

	xDir = 0;
	yDir = 0;
}

void Sprite::SetCurrAnimation(int idx) {
	if(idx >= 0 && idx < totalAnimations) {
		currAnimation = animations[idx];
	}
}

void Sprite::Update(Timer *timer) {
	if(!active) return;
	x += xDir * (timer->GetDeltaTime() / 10) * moveSpeed;
	y += yDir * (timer->GetDeltaTime() / 10) * moveSpeed;

	if(currAnimation)
		currAnimation->Update(timer);
}

void Sprite::Render(SDL_Renderer *renderer) {
	if(!active) return;

	if(currAnimation)
		currAnimation->Render(x, y, renderer);
}