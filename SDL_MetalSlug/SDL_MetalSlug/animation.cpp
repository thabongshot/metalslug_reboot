#include "animation.h"

Animation::Animation() {
	
}

Animation::Animation(SDL_Texture *sheet, int frames, int speed) {
	this->sheet = sheet;
	this->speed = speed;
	this->frames = frames;
	this->currFrame = 0;
	this->clips = new SDL_Rect[frames];

	int width, height;
	SDL_QueryTexture(sheet, NULL, NULL, &width, &height);

	for(int i = 0; i < frames; i++) {
		clips[i].x = i * width / frames;
		clips[i].y = 0;
		clips[i].w = width / frames;
		clips[i].h = height;
	}
	played = false;
	finished = true;

	stateTime = 0;
}

void Animation::Update(Timer *timer) {
	stateTime += timer->GetDeltaTime() / 10;
	currFrame = (stateTime) / speed;
	if(currFrame >= frames) {
		currFrame = currFrame % frames;
		finished = true;
	}
}

void Animation::Render(int x, int y, int camX, int camY, SDL_Renderer *renderer) {
	ApplySurface(x - clips[currFrame].w / 2 - camX + 400, y - clips[currFrame].h / 2 - camY + 300, sheet, renderer, &clips[currFrame]);
}