#include "sprite2d.h"

#include <vector>

Sprite2D::Sprite2D(const char *name) : Object(name)
{
	setTransform(new Transform());

	std::vector<Vertex> quad_vertices;
	quad_vertices.push_back(Vertex(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f()));
	quad_vertices.push_back(Vertex(Vector3f(-1.0f, 1.0f, 0.0f), Vector2f(0.0f, 1.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f()));
	quad_vertices.push_back(Vertex(Vector3f(1.0f, 1.0f, 0.0f), Vector2f(1.0f, 1.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f()));
	quad_vertices.push_back(Vertex(Vector3f(1.0f, -1.0f, 0.0f), Vector2f(1.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f()));
	std::vector<unsigned int> quad_indices;
	quad_indices.push_back(0);
	quad_indices.push_back(1);
	quad_indices.push_back(2);
	quad_indices.push_back(2);
	quad_indices.push_back(3);
	quad_indices.push_back(0);

	setMesh(new Mesh(quad_vertices, quad_indices, NULL, PhongShader::getInstance()));
}

Sprite2D::Sprite2D(const char *name, Transform *transform, Mesh *mesh) : Object(name, transform, mesh) 
{

}