#include "transform.h"
#include "technique.h"

Camera *Transform::camera;

float Transform::fov;
float Transform::width;
float Transform::height;

float Transform::zNear;
float Transform::zFar;

float Transform::left;
float Transform::right;
float Transform::bottom;
float Transform::top;

bool Transform::isPerspectiveMode;

Transform::Transform()
{
	translation = Vector3f(0, 0, 0);
	rotation = Vector3f(0, 0, 0);
	scale = Vector3f(1, 1, 1);
}

Transform::Transform(Vector3f translation, Vector3f rotation, Vector3f scale)
{
	this->translation = translation;
	this->rotation = rotation;
	this->scale = scale;
}

Vector3f Transform::getTranslation()
{
	return translation;
}

void Transform::setTranslation(Vector3f translation)
{
	this->translation = translation;
}

Vector3f Transform::getRotation()
{
	return rotation;
}

void Transform::setRotation(Vector3f rotation)
{
	this->rotation = rotation;
}

Vector3f Transform::getScale()
{
	return scale;
}

void Transform::setScale(Vector3f scale)
{
	this->scale = scale;
}

Matrix4f Transform::getTransformationMatrix()
{
	Matrix4f translationMatrix = initTranslationMatrix(translation);
	Matrix4f rotationMatrix = initRotationMatrix(rotation);
	Matrix4f scaleMatrix = initScaleMatrix(scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

Matrix4f Transform::getProjectionMatrix()
{
	if(isPerspectiveMode)
		return getPerspectiveProjTransformation();
	else
		return getOrthographicProjTransformation();
}

Matrix4f Transform::getPerspectiveProjTransformation()
{
	Matrix4f transformationMatrix = getTransformationMatrix();
	Matrix4f projectionMatrix = initProjectionMatrix(fov, width, height, zNear, zFar);
	Matrix4f cameraRotationMatrix = initCameraMatrix(camera->getForward(), camera->getUp());
	Matrix4f cameraTranslationMatrix = initTranslationMatrix(-camera->getPosition());

	return projectionMatrix * cameraRotationMatrix * cameraTranslationMatrix * transformationMatrix;
}

Matrix4f Transform::getOrthographicProjTransformation()
{
	Matrix4f transformationMatrix = getTransformationMatrix();
	Matrix4f projectionMatrix = initOrthographicProjectionMatrix(left, right, bottom, top, zNear, zFar);
	Matrix4f cameraRotationMatrix = initCameraMatrix(camera->getForward(), camera->getUp());
	Matrix4f cameraTranslationMatrix = initTranslationMatrix(-camera->getPosition());

	return projectionMatrix * cameraRotationMatrix * cameraTranslationMatrix * transformationMatrix;
}

void Transform::setPerspectiveProjection(float _fov, float _width, float _height, float _zNear, float _zFar)
{
	fov = _fov;
	width = _width;
	height = _height;
	zNear = _zNear;
	zFar = _zFar;

	isPerspectiveMode = true;
}

void Transform::setOrthographicProjection(float _left, float _right, float _bottom, float _top, float _zNear, float _zFar)
{
	left = _left;
	right = _right;
	bottom = _bottom;
	top = _top;
	zNear = _zNear;
	zFar = _zFar;

	isPerspectiveMode = false;
}

Camera *Transform::getCamera()
{
	return camera;
}

void Transform::setCamera(Camera *_camera)
{
	camera = _camera;
}