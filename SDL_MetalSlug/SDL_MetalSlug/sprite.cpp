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
	if(idx >= 0 && idx < totalAnimations) {
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
		currAnimation->Render(x, y, camX, camY, renderer);
}