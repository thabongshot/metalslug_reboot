#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "mymath.h"

class Vertex
{
private:
	Vector3f position;
	Vector2f texCoord;
	Vector3f normal;
	Vector3f bitangent;

public:
	Vertex();
	Vertex(Vector3f position, Vector2f texCoord, Vector3f normal, Vector3f bitangent);

	Vector3f getPosition();
	Vector2f getTexCoord();
	Vector3f getNormal();
	Vector3f getBiTangent();

	void setPostion(Vector3f position);
	void setTexCoord(Vector2f texCoord);
	void setNormal(Vector3f normal);
	void setBiTangent(Vector3f bitangent);
};

#endif