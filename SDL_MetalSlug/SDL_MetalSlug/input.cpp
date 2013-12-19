#include "input.h"

#include <stdio.h>

#define NUM_OF_KEYS 256

bool *Input::keys;

Input::Input() {
	keys = new bool[NUM_OF_KEYS];
}

void Input::Update(SDL_Event *e) {
	int keyCode = e->key.keysym.scancode;

	printf("%d\n", keyCode);

	if(keyCode >= 0 && keyCode < NUM_OF_KEYS) {
		if(e->key.state == SDL_KEYDOWN)
			keys[keyCode] = true;
		else if(e->key.state == SDL_KEYUP)
			keys[keyCode] = false;
	}
}

bool Input::isKeyPressed(int key) {
	if(key >= 0 && key < NUM_OF_KEYS) {
		return keys[key];
	}

	return false;
}