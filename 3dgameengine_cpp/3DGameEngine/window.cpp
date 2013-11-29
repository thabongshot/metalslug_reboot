#include "window.h"

#include <freeglut-2.8.1\include\GL\freeglut.h>

void Window::createWindow(int width, int height, const char *title)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);

	int xPos = (glutGet(GLUT_SCREEN_WIDTH) - width) / 2;
	int yPos = (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2;

	glutInitWindowPosition(xPos, yPos);
	glutCreateWindow(title);
}