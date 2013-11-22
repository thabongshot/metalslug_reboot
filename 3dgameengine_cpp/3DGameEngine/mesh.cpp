#include "glew-1.10.0\include\GL\glew.h"

#include "mesh.h"

#include "assimp\include\Importer.hpp"
#include "assimp\include\scene.h"
#include "assimp\include\postprocess.h"

#include <fstream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material *material, Shader *shader)
{
	setData(vertices, indices);
	this->shader = shader;
	this->material = material;
}

Mesh::Mesh(const char *fileName, Material *material, Shader *shader)
{
	loadMesh(fileName);
	this->shader = shader;
	this->material = material;
}

void Mesh::loadMesh(const char *fileName)
{
	Assimp::Importer importer;
	const aiScene *scene;

	std::ifstream fin(fileName);
	if(!fin.fail())
		fin.close();
	else
	{
		fprintf(stderr, "Error: Cannot open file '%s'\n", fileName);
		fprintf(stderr, "'%s'\n", importer.GetErrorString());
		exit(1);
	}

	scene = importer.ReadFile(fileName, aiProcess_GenSmoothNormals | aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_CalcTangentSpace);

	if(!scene)
	{
		fprintf(stderr, "Error: '%s'\n", importer.GetErrorString());
		exit(1);
	}
	
	const aiMesh *paiMesh = scene->mMeshes[0];

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	const aiVector3D Zero(0, 0, 0);

	for(unsigned int i = 0; i < paiMesh->mNumVertices; i++)
	{
		const aiVector3D *pPos = &(paiMesh->mVertices[i]);
		const aiVector3D *pNormal = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &Zero;
		const aiVector3D *pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero;
		const aiVector3D *pBiTangent = paiMesh->HasTangentsAndBitangents() ? &(paiMesh->mBitangents[i]) : &Zero;

		Vertex v(Vector3f(pPos->x, pPos->y, pPos->z), Vector2f(pTexCoord->x, pTexCoord->y), Vector3f(pNormal->x, pNormal->y, pNormal->z), Vector3f(pBiTangent->x, pBiTangent->y, pBiTangent->z));

		vertices.push_back(v);
	}

	for(unsigned int i = 0; i < paiMesh->mNumFaces; i++)
	{
		const aiFace &face = paiMesh->mFaces[i];

		if(face.mNumIndices == 3)
		{
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}
		else if(face.mNumIndices == 4)
		{
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[2]);
			indices.push_back(face.mIndices[3]);
		}
	}

	setData(vertices, indices);
}

void Mesh::setData(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	indices_size = indices.size();
}

void Mesh::drawMesh(Transform *transform)
{
	shader->bind();
	if (transform)
		shader->updateUniforms(transform->getTransformationMatrix(), transform->getProjectionMatrix(), material);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)32);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, indices_size, GL_UNSIGNED_INT, (const GLvoid*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}