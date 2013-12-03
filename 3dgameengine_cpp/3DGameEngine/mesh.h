#ifndef _MESH_H_
#define _MESH_H_

#include "shader.h"
#include <vector>
#include "vertex.h"
#include "transform.h"

#include <freeglut-2.8.1\include\GL\freeglut.h>

class Mesh
{
protected:
	GLuint vbo;
	GLuint ibo;
	unsigned int indices_size;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

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

	virtual void drawMesh(Transform *transform);
};

class Sprite : public Mesh
{
private:
	int rows;
	unsigned int *colsPerRow;

	int currRow;
	int currCol;

	float speed;

	bool isLoop;

	float stateTime;

	void update();

public:
	Sprite(Material *material, Shader *shader, int rows, unsigned int *colsPerRow, float speed, bool isLoop);

	virtual void drawMesh(Transform *transform);
};

#endif