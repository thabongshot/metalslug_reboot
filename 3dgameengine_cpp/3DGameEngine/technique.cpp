#define _CRT_SECURE_NO_WARNINGS

#include "technique.h"

#include <assert.h>
#include <string>
#include <stdlib.h>
#include <Windows.h>

Matrix4f initTranslationMatrix(Vector3f translation)
{
	Matrix4f r;

	r.m[0][0] = 1;	r.m[0][1] = 0;	r.m[0][2] = 0;	r.m[0][3] = translation.x;
	r.m[1][0] = 0;	r.m[1][1] = 1;	r.m[1][2] = 0;	r.m[1][3] = translation.y;
	r.m[2][0] = 0;	r.m[2][1] = 0;	r.m[2][2] = 1;	r.m[2][3] = translation.z;
	r.m[3][0] = 0;	r.m[3][1] = 0;	r.m[3][2] = 0;	r.m[3][3] = 1;

	return r;
}

Matrix4f initRotationMatrix(Vector3f rotation)
{
	Matrix4f rx, ry, rz;

	float sinX = sinf(RADIANS(rotation.x));
	float cosX = cosf(RADIANS(rotation.x));
	float sinY = sinf(RADIANS(rotation.y));
	float cosY = cosf(RADIANS(rotation.y));
	float sinZ = sinf(RADIANS(rotation.z));
	float cosZ = cosf(RADIANS(rotation.z));

	rx.m[0][0] = 1;		rx.m[0][1] = 0;		rx.m[0][2] = 0;		rx.m[0][3] = 0;
	rx.m[1][0] = 0;		rx.m[1][1] = cosX;	rx.m[1][2] = -sinX;	rx.m[1][3] = 0;
	rx.m[2][0] = 0;		rx.m[2][1] = sinX;	rx.m[2][2] = cosX;	rx.m[2][3] = 0;
	rx.m[3][0] = 0;		rx.m[3][1] = 0;		rx.m[3][2] = 0;		rx.m[3][3] = 1;

	ry.m[0][0] = cosY;	ry.m[0][1] = 0;		ry.m[0][2] = -sinY;	ry.m[0][3] = 0;
	ry.m[1][0] = 0;		ry.m[1][1] = 1;		ry.m[1][2] = 0;		ry.m[1][3] = 0;
	ry.m[2][0] = sinY;	ry.m[2][1] = 0;		ry.m[2][2] = cosY;	ry.m[2][3] = 0;
	ry.m[3][0] = 0;		ry.m[3][1] = 0;		ry.m[3][2] = 0;		ry.m[3][3] = 1;

	rz.m[0][0] = cosZ;	rz.m[0][1] = -sinZ;	rz.m[0][2] = 0;		rz.m[0][3] = 0;
	rz.m[1][0] = sinZ;	rz.m[1][1] = cosZ;	rz.m[1][2] = 0;		rz.m[1][3] = 0;
	rz.m[2][0] = 0;		rz.m[2][1] = 0;		rz.m[2][2] = 1;		rz.m[2][3] = 0;
	rz.m[3][0] = 0;		rz.m[3][1] = 0;		rz.m[3][2] = 0;		rz.m[3][3] = 1;

	return rz * (ry * rx);
}

Matrix4f initScaleMatrix(Vector3f scale)
{
	Matrix4f r;

	r.m[0][0] = scale.x;	r.m[0][1] = 0;			r.m[0][2] = 0;			r.m[0][3] = 0;
	r.m[1][0] = 0;			r.m[1][1] = scale.y;	r.m[1][2] = 0;			r.m[1][3] = 0;
	r.m[2][0] = 0;			r.m[2][1] = 0;			r.m[2][2] = scale.z;	r.m[2][3] = 0;
	r.m[3][0] = 0;			r.m[3][1] = 0;			r.m[3][2] = 0;			r.m[3][3] = 1;

	return r;
}

Matrix4f initProjectionMatrix(float fov, float width, float height, float zNear, float zFar)
{
	float aspectRatio = width / height;
	float tanHalfFov = tanf(RADIANS(fov / 2));
	float zRange = zNear - zFar;

	Matrix4f r;

	r.m[0][0] = 1.0f / (tanHalfFov * aspectRatio);	r.m[0][1] = 0;					r.m[0][2] = 0;							r.m[0][3] = 0;
	r.m[1][0] = 0;									r.m[1][1] = 1.0f / tanHalfFov;	r.m[1][2] = 0;							r.m[1][3] = 0;
	r.m[2][0] = 0;									r.m[2][1] = 0;					r.m[2][2] = (-zNear - zFar) / zRange;	r.m[2][3] = 2 * zFar * zNear / zRange;
	r.m[3][0] = 0;									r.m[3][1] = 0;					r.m[3][2] = 1;							r.m[3][3] = 0;

	return r;
}

Matrix4f initOrthographicProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
{
	Matrix4f r;

	r.m[0][0] = 2 / (right - left);	r.m[0][1] = 0;						r.m[0][2] = 0;						r.m[0][3] = -(right + left) / (right - left);
	r.m[1][0] = 0;					r.m[1][1] = 2 / (top - bottom);		r.m[1][2] = 0;						r.m[1][3] = -(top + bottom) / (top - bottom);
	r.m[2][0] = 0;					r.m[2][1] = 0;						r.m[2][2] = -2 / (zFar - zNear);	r.m[2][3] = -(zFar + zNear) / (zFar - zNear);
	r.m[3][0] = 0;					r.m[3][1] = 0;						r.m[3][2] = 0;						r.m[3][3] = 1;

	return r;
}

Matrix4f initCameraMatrix(Vector3f forward, Vector3f up)
{
	Vector3f f = forward.normalized();

	Vector3f r = up.normalized();

	r = r.cross(f);

	Vector3f u = f.cross(r);

	Matrix4f m;

	m.m[0][0] = r.x;	m.m[0][1] = r.y;	m.m[0][2] = r.z;	m.m[0][3] = 0;
	m.m[1][0] = u.x;	m.m[1][1] = u.y;	m.m[1][2] = u.z;	m.m[1][3] = 0;
	m.m[2][0] = f.x;	m.m[2][1] = f.y;	m.m[2][2] = f.z;	m.m[2][3] = 0;
	m.m[3][0] = 0;		m.m[3][1] = 0;		m.m[3][2] = 0;		m.m[3][3] = 1;

	return m;
}

wchar_t *charToWChar(const char *pstrSrc)
{
	assert(pstrSrc);
	int nLen = strlen(pstrSrc) + 1;

	wchar_t *pwstr = (LPWSTR)malloc(sizeof(wchar_t) * nLen);
	mbstowcs(pwstr, pstrSrc, nLen);

	return pwstr;
}

char *wCharToChar(const wchar_t *pwstrSrc)
{
	assert(pwstrSrc);

#if !defined _DEBUG
	int len = 0;
	len = (wcslen(pwstrSrc) + 1)*2;
	char *pstr = (char*)malloc(sizeof(char) * len);

	WideCharToMultiByte(949, 0, pwstrSrc, -1, pstr, len, NULL, NULL);
#else

	int nLen = wcslen(pwstrSrc);

	char *pstr = (char*)malloc(sizeof(char) * nLen + 1);
	wcstombs(pstr, pwstrSrc, nLen + 1);

#endif

	return pstr;
}