#ifndef _INPUT_H_
#define _INPUT_H_

#define NUMBER_OF_KEYS 257
#define NUMBER_OF_MOUSE_BUTTONS 5

#include "mymath.h"

class Input
{
private:
	static Input *pInstance;

	static bool lastKeys[NUMBER_OF_KEYS];
	static bool lastMouseButtons[NUMBER_OF_MOUSE_BUTTONS];

	static bool keys[NUMBER_OF_KEYS];
	static bool mouseButtons[NUMBER_OF_MOUSE_BUTTONS];

	static Vector2i cursorPos;

	Input();

public:
	static void init();

	static void update();

	static void keyDown(unsigned char c, int x, int y);
	static void keyDown(int code, int x, int y);

	static void keyUp(unsigned char c, int x, int y);
	static void keyUp(int code, int x, int y);

	static void motion(int x, int y);

	static bool isKeyDown(unsigned char c);
	static bool isKeyUp(unsigned char c);
	static bool isKeyReleased(unsigned char c);

	static void mouseButton(int button, int state, int x, int y);

	static bool isMouseButtonDown(int button);
	static bool isMouseButtonUp(int button);
	static bool isMouseButtonReleased(int button);

	static Vector2i getCursorPosition();
	static void setCursorPosition(Vector2i position);
};

#endif