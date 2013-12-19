#include "window.h"
#include "processor.h"
#include "testscene.h"

#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);

	Window *window = nullptr;
	Processor *mainProcessor = nullptr;

	window = new Window();
	window->InitWindow("Game", SCREEN_WIDTH, SCREEN_HEIGHT);

	mainProcessor = new Processor(window);
	mainProcessor->SetScene(new TestScene());

	mainProcessor->Run();

	delete mainProcessor;

	SDL_Quit();

	return 0;
}