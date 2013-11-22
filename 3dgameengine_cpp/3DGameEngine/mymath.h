#ifndef _MYMATH_H_
#define _MYMATH_H_

#include <math.h>
#include <stdlib.h>

#define PI 3.141592f

#define RADIANS(a) a * PI / 180.0f

struct Vector2i
{
	int x, y;

	Vector2i()
	{
		x = 0;
		y = 0;
	}

	Vector2i(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

inline Vector2i operator - (Vector2i a, Vector2i b)
{
	return Vector2i(a.x - b.x, a.y - b.y);
}

struct Vector2f
{
	float x, y;

	Vector2f()
	{
		x = 0;
		y = 0;
	}

	Vector2f(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float length();

	Vector2f normalized();

	float dot(Vector2f v);
};

inline Vector2f operator + (Vector2f a, Vector2f b)
{
	return Vector2f(a.x + b.x, a.y + b.y);
}

inline Vector2f operator - (Vector2f a, Vector2f b)
{
	return Vector2f(a.x - b.x, a.y - b.y);
}

inline Vector2f operator * (Vector2f a, Vector2f b)
{
	return Vector2f(a.x * b.x, a.y * b.y);
}

inline Vector2f operator / (Vector2f a, Vector2f b)
{
	return Vector2f(a.x / b.x, a.y / b.y);
}

struct Vector3f
{
	float x, y, z;

	Vector3f()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float length();

	Vector3f normalized();

	float dot(Vector3f v);

	Vector3f cross(Vector3f v);

	Vector3f rotate(float angle, Vector3f axis);
};

inline Vector3f operator + (Vector3f a, Vector3f b)
{
	return Vector3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vector3f operator - (Vector3f a, Vector3f b)
{
	return Vector3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vector3f operator - (Vector3f a)
{
	return Vector3f(-a.x, -a.y, -a.z);
}

inline Vector3f operator * (Vector3f a, Vector3f b)
{
	return Vector3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline Vector3f operator * (Vector3f a, float b)
{
	return Vector3f(a.x * b, a.y * b, a.z * b);
}

inline Vector3f operator * (float a, Vector3f b)
{
	return b * a;
}

inline Vector3f operator / (Vector3f a, Vector3f b)
{
	return Vector3f(a.x / b.x, a.y / b.y, a.z / b.z);
}

inline bool operator == (Vector3f a, Vector3f b)
{
	return(a.x == b.x && a.y == b.y && a.z == b.z);
}

inline bool operator != (Vector3f a, Vector3f b)
{
	return !(a==b);
}

struct Quaternion
{
	float x, y, z, w;

	Quaternion()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Quaternion(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	float length();

	Quaternion normalized();

	Quaternion conjugated();
};

inline Quaternion operator * (Quaternion a, Quaternion b)
{
	float ww = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	float xx = a.x * b.w + a.w * b.x + a.y * b.z - a.z * b.y;
	float yy = a.y * b.w + a.w * b.y + a.z * b.x - a.x * b.z;
	float zz = a.z * b.w + a.w * b.z + a.x * b.y - a.y * b.x;

	return Quaternion(xx, yy, zz, ww);
}

inline Quaternion operator * (Quaternion a, Vector3f b)
{
	float ww = -a.x * b.x - a.y * b.y - a.z * b.z;
	float xx = a.w * b.x + a.y * b.z - a.z * b.y;
	float yy = a.w * b.y + a.z * b.x - a.x * b.z;
	float zz = a.w * b.z + a.x * b.y - a.y * b.x;

	return Quaternion(xx, yy, zz, ww);
}

inline Quaternion operator * (Vector3f a, Quaternion b)
{
	return b * a;
}

struct Matrix4f
{
	float m[4][4];

	Matrix4f()
	{
		
	}
};

inline Matrix4f operator * (Matrix4f a, Matrix4f b)
{
	Matrix4f result = Matrix4f();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			result.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
		}
	}

	return result;
}

#endif