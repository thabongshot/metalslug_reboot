#ifndef _MESH_H_
#define _MESH_H_

#include "shader.h"
#include <vector>
#include "vertex.h"
#include "transform.h"

#include "freeglut-2.8.1\include\GL\freeglut.h"

class Mesh
{
private:
	GLuint vbo;
	GLuint ibo;
	unsigned int indices_size;

	Shader *shader;

	Material *material;

	void setData(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	void loadMesh(const char *fileName);

public:
	Mesh()
	{
		vbo = 0;
		ibo = 0;
		indices_size = 0;
	}

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material *material, Shader *shader);

	Mesh(const char *fileName, Material *material, Shader *shader);

	void drawMesh(Transform *transform);
};

#endif