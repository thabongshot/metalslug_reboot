#include "vertex.h"

Vertex::Vertex()
{
	position = Vector3f(0, 0, 0);
	texCoord = Vector2f(0, 0);
	normal = Vector3f(0, 0, 0);
	bitangent = Vector3f(0, 0, 0);
}

Vertex::Vertex(Vector3f position, Vector2f texCoord, Vector3f normal, Vector3f bitangent)
{
	this->position = position;
	this->texCoord = texCoord;
	this->normal = normal;
	this->bitangent = bitangent;
}

Vector3f Vertex::getPosition()
{
	return position;
}

Vector2f Vertex::getTexCoord()
{
	return texCoord;
}

Vector3f Vertex::getNormal()
{
	return normal;
}

Vector3f Vertex::getBiTangent()
{
	return bitangent;
}

void Vertex::setPostion(Vector3f position)
{
	this->position = position;
}

void Vertex::setTexCoord(Vector2f texCoord)
{
	this->texCoord = texCoord;
}

void Vertex::setNormal(Vector3f normal)
{
	this->normal = normal;
}

void Vertex::setBiTangent(Vector3f bitangent)
{
	this->bitangent = bitangent;
}
