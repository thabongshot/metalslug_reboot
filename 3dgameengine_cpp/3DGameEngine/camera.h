#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "mymath.h"

#include <freeglut-2.8.1\include\GL\freeglut.h>


class Camera
{
private:
	Vector3f yAxis;

	Vector3f position;
	Vector3f forward;
	Vector3f up;

	bool mouseLocked;

public:
	Camera();
	Camera(Vector3f position, Vector3f forward, Vector3f up);

	void move(Vector3f direction, float amount);

	void rotateY(float angle);
	void rotateX(float angle);

	Vector3f getLeft();
	Vector3f getRight();

	Vector3f getPosition();
	void setPosition(Vector3f position);

	Vector3f getForward();
	void setForward(Vector3f forward);

	Vector3f getUp();
	void setUp(Vector3f up);

	void input();
	virtual void update();
};

#endif