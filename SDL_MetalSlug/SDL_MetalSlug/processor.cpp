#include "processor.h"

Processor::Processor(Window *window) : windowPtr(window), quit(false) {
	scene = nullptr;
}

void Processor::SetScene(Scene *scene) {
	this->scene = scene;
	this->scene->Init(windowPtr->getRenderer());
}

void Processor::Run() {
	if(windowPtr) {
		Timer *timer = new Timer();

		SDL_Event e;

		timer->Start();

		while(!quit) {
			while(SDL_PollEvent(&e)) {
				// Handle events such as input
				HandleEvents(&e);
			}

			// Update process
			Update(timer);

			timer->Update();

			// Render Window
			Render();
		}

		delete timer;

		windowPtr->DestroyWindow();
	}
}

void Processor::HandleEvents(SDL_Event *e) {
	if(e->type == SDL_QUIT)
		quit = true;

	if(scene)
			scene->Input(e);
}

void Processor::Update(Timer *timer) {
	// Do logic update here!
	if(scene)
		scene->Update(timer);
}

void Processor::Render() {
	SDL_RenderClear(windowPtr->getRenderer());

	// Do rendering here!
	if(scene)
		scene->Render(windowPtr->getRenderer());

	windowPtr->UpdateWindow();
}

SDL_Renderer *Processor::GetRenderer() {
	if(windowPtr)
		return windowPtr->getRenderer();
	return nullptr;
}