#include "utils.h"

SDL_Texture *loadTexture(SDL_Renderer *renderer, std::string filePath) {
	SDL_Surface *image = nullptr;
	SDL_Texture *tex = nullptr;

	image = SDL_LoadBMP(filePath.c_str());
	if(image) {
		tex = SDL_CreateTextureFromSurface(renderer, image);
		SDL_FreeSurface(image);
	}
	else {
		fprintf(stderr, "Error: '%s'\n", SDL_GetError());
	}

	return tex;
}

SDL_Texture *loadTextureExt(SDL_Renderer *renderer, std::string filePath) {
	SDL_Texture *tex = nullptr;
	tex = IMG_LoadTexture(renderer, filePath.c_str());
	if(!tex) {
		throw std::runtime_error("Failed to load image: " + filePath + IMG_GetError());
	}

	return tex;
}

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *renderer, SDL_Rect *clip = NULL) {
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	if(clip != NULL) {
		pos.w = clip->w;
		pos.h = clip->h;
	}
	else
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);

	SDL_RenderCopy(renderer, tex, clip, &pos);
}