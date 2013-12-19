#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL.h>

class Window {
private:
	int width;
	int height;
	const char *title;

	SDL_Window *windowPtr;
	SDL_Renderer *rendererPtr;

public:
	Window();
	Window(const Window &other);
	~Window();

	void InitWindow(const char *title, int width, int height);

	SDL_Window *getWindow();

	SDL_Renderer *getRenderer();

	void DestroyWindow();

	void UpdateWindow();
};

#endif