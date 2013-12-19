#ifndef _UTILS_H_
#define _UTILS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdexcept>
#include <string>

SDL_Texture *loadTexture(SDL_Renderer *renderer, std::string filePath);

SDL_Texture *loadTextureExt(SDL_Renderer *renderer, std::string filePath);

void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *renderer, SDL_Rect *clip);

#endif