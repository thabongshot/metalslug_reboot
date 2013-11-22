#include "camera.h"

#include "input.h"
#include "time.h"

#include <stdio.h>

Vector2i centerPos;

Camera::Camera()
{
	mouseLocked = false;
	centerPos = Vector2i(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	yAxis = Vector3f(0, 1, 0);

	position = Vector3f(0, 0, 0);
	forward = Vector3f(0, 0, 1);
	up = Vector3f(0, 1, 0);
}

Camera::Camera(Vector3f position, Vector3f forward, Vector3f up)
{
	mouseLocked = false;
	centerPos = Vector2i(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	yAxis = Vector3f(0, 1, 0);

	this->position = position;
	this->forward = forward.normalized();
	this->up = up.normalized();
}

void Camera::move(Vector3f direction, float amount)
{
	position = position + (direction * amount);
}

void Camera::rotateY(float angle)
{
	Vector3f hAxis = (yAxis.cross(forward)).normalized();

	forward = (forward.rotate(angle, yAxis)).normalized();

	up = (forward.cross(hAxis)).normalized();
}

void Camera::rotateX(float angle)
{
	Vector3f hAxis = (yAxis.cross(forward)).normalized();

	forward = (forward.rotate(angle, hAxis)).normalized();

	up = (forward.cross(hAxis)).normalized();
}

Vector3f Camera::getLeft()
{
	return (forward.cross(up)).normalized();
}

Vector3f Camera::getRight()
{
	return (up.cross(forward)).normalized();
}

Vector3f Camera::getPosition()
{
	return position;
}

void Camera::setPosition(Vector3f position)
{
	this->position = position;
}

Vector3f Camera::getForward()
{
	return forward;
}

void Camera::setForward(Vector3f forward)
{
	this->forward = forward;
}

Vector3f Camera::getUp()
{
	return up;
}

void Camera::setUp(Vector3f up)
{
	this->up = up;
}

void Camera::input()
{
	float sensitivity = 0.5f;
	float moveAmount = (float)(10.0 * Time::getDelta());

	if(Input::isKeyReleased(27))
	{
		glutSetCursor(GLUT_CURSOR_INHERIT);
		mouseLocked = false;
	}

	if(Input::isMouseButtonReleased(GLUT_LEFT_BUTTON))
	{
		Input::setCursorPosition(centerPos);
		glutSetCursor(GLUT_CURSOR_NONE);
		mouseLocked = true;
	}

	if(Input::isKeyDown('w'))
		move(getForward(), moveAmount);
	if(Input::isKeyDown('s'))
		move(getForward(), -moveAmount);
	if(Input::isKeyDown('a'))
		move(getLeft(), moveAmount);
	if(Input::isKeyDown('d'))
		move(getRight(), moveAmount);

	if(mouseLocked)
	{
		Vector2i deltaPos = Input::getCursorPosition() - centerPos;

		bool rotY = deltaPos.x != 0;
		bool rotX = deltaPos.y != 0;

		if(rotY)
		{
			//printf("deltaY: %d\n", deltaPos.y);
			rotateY((float)deltaPos.x * sensitivity);
		}
		if(rotX)
		{
			//printf("deltaX: %d\n", deltaPos.x);
			rotateX((float)deltaPos.y * sensitivity);
		}

		if(rotX || rotY)
			Input::setCursorPosition(centerPos);
	}
}

void Camera::update()
{

}