#ifndef _TECHNIQUE_H_
#define _TECHNIQUE_H_

#include "mymath.h"

Matrix4f initTranslationMatrix(Vector3f translation);
Matrix4f initRotationMatrix(Vector3f rotation);
Matrix4f initScaleMatrix(Vector3f scale);
Matrix4f initProjectionMatrix(float fov, float width, float height, float zNear, float zFar);
Matrix4f initOrthographicProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar);
Matrix4f initCameraMatrix(Vector3f forward, Vector3f up);

wchar_t *charToWChar(const char *pstrSrc);
char *wCharToChar(const wchar_t *pwstrSrc);

#endif