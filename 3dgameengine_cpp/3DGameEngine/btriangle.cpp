#include "btriangle.h"

#include <vector>

bTriangle::bTriangle()
{
	std::vector<Vertex> vertices;

	vertices.push_back(Vertex(Vector3f(0, 1, 0), Vector2f(0.5f, 1), Vector3f(0, 0, 0)));
	vertices.push_back(Vertex(Vector3f(1, -1, 0), Vector2f(1, 0), Vector3f(0, 0, 0)));
	vertices.push_back(Vertex(Vector3f(-1, -1, 0), Vector2f(0, 0), Vector3f(0, 0, 0)));

	std::vector<unsigned int> indices;

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	mesh = new Mesh(vertices, indices);
}

void bTriangle::drawMesh()
{
	if(mesh)
		mesh->drawMesh();
}