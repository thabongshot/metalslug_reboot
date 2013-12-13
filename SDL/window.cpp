#include "window.h"

Window::Window() {
	windowPtr = nullptr;
	rendererPtr = nullptr;
}

Window::Window(const Window &other) {
	this->windowPtr = other.windowPtr;
	this->rendererPtr = other.rendererPtr;
}

Window::~Window() {
	
}

void Window::InitWindow(const char *title, int width, int height) {
	this->title = title;
	this->width = width;
	this->height = height;

	windowPtr = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	rendererPtr = SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Window::DestroyWindow() {
	SDL_DestroyRenderer(rendererPtr);
	SDL_DestroyWindow(windowPtr);
}

SDL_Window *Window::getWindow() {
	return windowPtr;
}

SDL_Renderer *Window::getRenderer() {
	return rendererPtr;
}

void Window::UpdateWindow() {
	SDL_RenderPresent(rendererPtr);
}