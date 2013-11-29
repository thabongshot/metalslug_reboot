#define GLEW_STATIC

#if WIN32
//#pragma comment (linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

#include <glew-1.10.0\include\GL\glew.h>

#include <freeglut-2.8.1\include\GL\freeglut.h>

#include <DevIL\include\IL\ilut.h>

#include "mainComponent.h"
#include "window.h"
#include "renderUtil.h"
#include "input.h"
#include "scene.h"
#include "time.h"
#include "lua_backend.h"

#include <stdio.h>

void _update(int value);
void _render(void);

const double frameTime = 1.0 / FRAME_CAP;
double lastTime;
double unprocessedTime;

int frames;
double frameCounter;

bool renderable;

MainComponent *engine;
Scene *scene;

bool MainComponent::closeRequested;

MainComponent::MainComponent(int *argc, char **argv)
{
	init(argc, argv);
	initCallbacks();
	run();
	cleanUp();
}

void MainComponent::init(int *argc, char **argv)
{
	glutInit(argc, argv);
	Window::createWindow(WIDTH, HEIGHT, TITLE);
	initGraphics();

	GLuint glewOK = glewInit();
	if(glewOK != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(glewOK));
		exit(1);
	}

	initDevIL();
	
	if(!initLUAState())
		exit(1);
	

	Input::init();
	scene = new Scene();

	lastTime = glutGet(GLUT_ELAPSED_TIME);
	unprocessedTime = 0;
	frames = 0;
	frameCounter = 0;

	closeRequested = false;

	initFXAA();
	setFXAAEnabled(true);

	// For Testing Tessellation!
	GLint maxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxPatchVertices);
	printf("Tessellation Test: Max supported patch vertices %d\n", maxPatchVertices);
}

void MainComponent::initCallbacks()
{
	glutTimerFunc(1, _update, 1);
	glutIdleFunc(_render);
	glutDisplayFunc(_render);

	glutKeyboardFunc(Input::keyDown);
	glutSpecialFunc(Input::keyDown);
	glutKeyboardUpFunc(Input::keyUp);
	glutSpecialUpFunc(Input::keyUp);

	glutMouseFunc(Input::mouseButton);
	glutMotionFunc(Input::motion);
	glutPassiveMotionFunc(Input::motion);
}

void MainComponent::initDevIL()
{
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	ilutEnable(ILUT_OPENGL_CONV);
}

void MainComponent::run()
{
	glutMainLoop();
}

void MainComponent::update()
{
	renderable = false;

	double startTime = Time::getTime();
	double passedTime = (double)startTime - (double)lastTime;

	lastTime = startTime;

	unprocessedTime += passedTime / SECOND;
	frameCounter += passedTime;

	while(unprocessedTime > frameTime)
	{
		renderable = true;

		unprocessedTime -= frameTime;

		Time::setDelta(frameTime);

		scene->input();
		Input::update();

		scene->update();

		if(frameCounter >= SECOND)
		{
			printf("FPS: %d\n", frames);
			frames = 0;
			frameCounter = 0;
		}
	}

	if (closeRequested)
	{
		cleanUp();
		glutLeaveMainLoop();
		return;
	}
}

void MainComponent::render()
{
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	if(renderable)
	{
		prepareRender();
		scene->render();
		postRender();

		frames++;
	}

	glutSwapBuffers();
}

void MainComponent::cleanUp()
{
	terminateLUAState();
	delete scene;
}

void MainComponent::postMsg(MSGTYPE msg)
{
	switch(msg)
	{
	case MSG_QUIT:
		closeRequested = true;
		return;
	}
}

void _update(int value)
{
	engine->update();

	glutPostRedisplay();

	glutTimerFunc(1, _update, 1);
}

void _render()
{
	engine->render();
}

int main(int argc, char **argv)
{
	engine = new MainComponent(&argc, argv);

	delete engine;

	return 0;
}