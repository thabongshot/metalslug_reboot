#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "camera.h"

class Transform
{
private:
	Vector3f translation;
	Vector3f rotation;
	Vector3f scale;

	static Camera *camera;

	static float zNear;
	static float zFar;

	static float width;
	static float height;
	static float fov;

	static float left;
	static float right;
	static float bottom;
	static float top;

	static bool isPerspectiveMode;

	Matrix4f getPerspectiveProjTransformation();

	Matrix4f getOrthographicProjTransformation();

public:
	Transform();
	Transform(Vector3f translation, Vector3f rotation, Vector3f scale);

	Vector3f getTranslation();
	void setTranslation(Vector3f translation);

	Vector3f getRotation();
	void setRotation(Vector3f rotation);

	Vector3f getScale();
	void setScale(Vector3f scale);

	Matrix4f getTransformationMatrix();

	Matrix4f getProjectionMatrix();

	static void setPerspectiveProjection(float _fov, float _width, float _height, float _zNear, float _zFar);
	static void setOrthographicProjection(float _left, float _right, float _bottom, float _top, float _zNear, float _zFar);

	static Camera *getCamera();

	static void setCamera(Camera *_camera);
};

#endif