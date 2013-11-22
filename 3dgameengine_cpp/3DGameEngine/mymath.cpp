#include "mymath.h"

float Vector2f::length()
{
	return sqrtf(x * x + y * y);
}

Vector2f Vector2f::normalized()
{
	float length_val = length();

	return Vector2f(x / length_val, y / length_val);
}

float Vector2f::dot(Vector2f v)
{
	return x * v.x + y * v.y;
}

float Vector3f::length()
{
	return sqrtf(x * x + y * y + z * z);
}

Vector3f Vector3f::normalized()
{
	float length_val = length();

	return Vector3f(x / length_val, y / length_val, z / length_val);
}

float Vector3f::dot(Vector3f v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3f Vector3f::cross(Vector3f v)
{
	float xx = y * v.z - z * v.y;
	float yy = z * v.x - x * v.z;
	float zz = x * v.y - y * v.x;

	return Vector3f(xx, yy, zz);
}

Vector3f Vector3f::rotate(float angle, Vector3f axis)
{
	float sinHalfAngle = sinf(RADIANS(angle / 2.0f));
	float cosHalfAngle = cosf(RADIANS(angle / 2.0f));

	float rX = axis.x * sinHalfAngle;
	float rY = axis.y * sinHalfAngle;
	float rZ = axis.z * sinHalfAngle;
	float rW = cosHalfAngle;

	Quaternion rotation = Quaternion(rX, rY, rZ, rW);
	Quaternion conjugate = rotation.conjugated();

	Quaternion r = rotation * (*this) * conjugate;

	return Vector3f(r.x, r.y, r.z);
}

float Quaternion::length()
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalized()
{
	float length_val = length();

	return Quaternion(x / length_val, y / length_val, z / length_val, w / length_val);
}

Quaternion Quaternion::conjugated()
{
	return Quaternion(-x, -y, -z, w);
}