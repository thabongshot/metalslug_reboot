#include "bcube.h"

#include <vector>

bCube::bCube()
{
	std::vector<Vertex> vertices;
	vertices.push_back(Vertex(Vector3f(-1, -1, 1), Vector2f(0, 0), Vector3f(0, 0, 0)));
	vertices.push_back(Vertex(Vector3f(-1, 1, 1), Vector2f(0, 1), Vector3f(0, 0, 0)));
	vertices.push_back(Vertex(Vector3f(1, 1, 1), Vector2f(1, 1), Vector3f(0, 0, 0)));
	vertices.push_back(Vertex(Vector3f(1, -1, 1), Vector2f(1, 0), Vector3f(0, 0, 0)));
	vertices.push_back(Vertex(Vector3f(-1, -1, -1), Vector2f(0, 0), Vector3f(0, 0, 0)));
	vertices.push_back(Vertex(Vector3f(-1, 1, -1), Vector2f(0, 1), Vector3f(0, 0, 0)));
	vertices.push_back(Vertex(Vector3f(1, 1, -1), Vector2f(1, 1), Vector3f(0, 0, 0)));
	vertices.push_back(Vertex(Vector3f(1, -1, -1), Vector2f(1, 0), Vector3f(0, 0, 0)));

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(1);
	indices.push_back(4);
	indices.push_back(1);
	indices.push_back(0);

	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(2);
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(2);
	indices.push_back(6);
	indices.push_back(7);
	indices.push_back(2);
	indices.push_back(7);
	indices.push_back(3);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(7);
	indices.push_back(0);
	indices.push_back(7);
	indices.push_back(4);

	indices.push_back(7);
	indices.push_back(6);
	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(4);

	mesh = new Mesh(vertices, indices);
}

void bCube::drawMesh()
{
	if(mesh)
		mesh->drawMesh();
}