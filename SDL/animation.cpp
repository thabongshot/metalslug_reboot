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
}

void Animation::Update(Timer *timer) {
	currFrame = (timer->GetElapsedTime() / 100 * speed) % frames;
}

void Animation::Render(int x, int y, SDL_Renderer *renderer) {
	ApplySurface(x, y, sheet, renderer, &clips[currFrame]);
}