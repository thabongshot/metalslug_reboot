#include "freeglut-2.8.1\include\GL\freeglut.h"

#include "time.h"

double Time::delta;

double Time::getTime()
{
	return (double)glutGet(GLUT_ELAPSED_TIME);
}

double Time::getDelta()
{
	return delta;
}

void Time::setDelta(double _delta)
{
	delta = _delta;
}