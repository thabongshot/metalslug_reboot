#include "input.h"

#include <freeglut-2.8.1\include\GL\freeglut.h>

#include <stdio.h>

Input *Input::pInstance;
bool Input::keys[NUMBER_OF_KEYS];
bool Input::lastKeys[NUMBER_OF_KEYS];
bool Input::mouseButtons[NUMBER_OF_MOUSE_BUTTONS];
bool Input::lastMouseButtons[NUMBER_OF_MOUSE_BUTTONS];
Vector2i Input::cursorPos;

Input::Input()
{
	for(int i = 0; i < NUMBER_OF_KEYS; i++)
	{
		keys[i] = false;
		lastKeys[i] = false;
	}

	for(int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++)
	{
		lastMouseButtons[i] = false;
		mouseButtons[i] = false;
	}
}

void Input::init()
{
	if(!pInstance)
		pInstance = new Input();
}

void Input::update()
{
	for(int i = 0; i < NUMBER_OF_KEYS; i++)
	{
		lastKeys[i] = keys[i];
	}

	for(int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++)
	{
		lastMouseButtons[i] = mouseButtons[i];
	}
}

void Input::keyDown(unsigned char c, int x, int y)
{
	keys[c] = true;
}

void Input::keyDown(int code, int x, int y)
{

}

void Input::keyUp(unsigned char c, int x, int y)
{
	keys[c] = false;
}

void Input::keyUp(int code, int x, int y)
{

}

void Input::mouseButton(int button, int state, int x, int y)
{
	if(button >= 0 && button < NUMBER_OF_MOUSE_BUTTONS)
	{
		if(state == GLUT_DOWN)
			mouseButtons[button] = true;
		if(state == GLUT_UP)
			mouseButtons[button] = false;
	}
}

void Input::motion(int x, int y)
{
	cursorPos.x = x;
	cursorPos.y = y;
}

bool Input::isKeyDown(unsigned char c)
{
	return keys[c];
}

bool Input::isKeyReleased(unsigned char c)
{
	return lastKeys[c] && !keys[c];
}

bool Input::isKeyUp(unsigned char c)
{
	return !keys[c];
}

bool Input::isMouseButtonDown(int button)
{
	if(button >= 0 && button < NUMBER_OF_MOUSE_BUTTONS)
		return mouseButtons[button];

	return false;
}

bool Input::isMouseButtonReleased(int button)
{
	if(button >= 0 && button < NUMBER_OF_MOUSE_BUTTONS)
		return lastMouseButtons[button] && !mouseButtons[button];

	return false;
}

bool Input::isMouseButtonUp(int button)
{
	if(button >= 0 && button < NUMBER_OF_MOUSE_BUTTONS)
		return !mouseButtons[button];

	return false;
}

Vector2i Input::getCursorPosition()
{
	return cursorPos;
}

void Input::setCursorPosition(Vector2i position)
{
	cursorPos = position;
	glutWarpPointer(position.x, position.y);
}