#include "renderUtil.h"

#include <glew-1.10.0\include\GL\glew.h>

#include <freeglut-2.8.1\include\GL\freeglut.h>

#include "shader.h"
#include "mesh.h"

unsigned int FXAAFramebuffer;
unsigned int renderedTexture;
unsigned int texID;
unsigned int rcpFrameID;
Shader *fxaaShader;
Mesh *screenQuad;
bool FXAAEnabled;

bool initFramebuffer();

void initGraphics()
{
	glClearColor(0, 0, 0, 0);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_DEPTH_CLAMP);

	glEnable(GL_TEXTURE_2D);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void unbindTextures()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void initFXAA()
{
	fxaaShader = new Shader();
	fxaaShader->addVertexShaderFromFile("shaders/FXAA2.vs");
	fxaaShader->addFragmentShaderFromFile("shaders/FXAA2.fs");
	fxaaShader->compileShader();
	if (!initFramebuffer())
	{
		fprintf(stderr, "Cannot initialize framebuffer.\n");
		getchar();
		exit(1);
	}
	texID = fxaaShader->getUniformLocation("renderedTexture");
	rcpFrameID = fxaaShader->getUniformLocation("rcpFrame");

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
	screenQuad = new Mesh(quad_vertices, quad_indices, NULL, fxaaShader);
}

void setFXAAEnabled(bool value)
{
	FXAAEnabled = value;
}

bool initFramebuffer()
{
	FXAAFramebuffer = 0;
	glGenFramebuffers(1, &FXAAFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, FXAAFramebuffer);

	glGenTextures(1, &renderedTexture);

	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	GLenum DrawBuffers[2] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;

	return true;
}

void prepareRender()
{
	if (!FXAAEnabled)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	else
		glBindFramebuffer(GL_FRAMEBUFFER, FXAAFramebuffer);
}

void postRender()
{
	if (FXAAEnabled)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		fxaaShader->bind();
		glUniform2f(rcpFrameID, 1.0f / (float)WIDTH, 1.0f / (float)HEIGHT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		glUniform1i(texID, 0);

		screenQuad->drawMesh(NULL);
	}
}