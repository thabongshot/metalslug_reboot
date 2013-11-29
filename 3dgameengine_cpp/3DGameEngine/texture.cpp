#include "texture.h"

#include "technique.h"

#include <freeglut-2.8.1\include\GL\freeglut.h>

#include <DevIL\include\IL\ilut.h>

Texture::Texture()
{
	id = 0;
}

Texture::Texture(const char *fileName)
{
	id = loadTexture(fileName);
}

Texture::Texture(unsigned int id)
{
	this->id = id;
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

unsigned int Texture::getID()
{
	return id;
}

unsigned int Texture::loadTexture(const char *fileName)
{
	ILuint imageID;

	GLuint textureID;

	ILboolean success;

	ILenum error;

	ilGenImages(1, &imageID);

	ilBindImage(imageID);

	wchar_t *wFileName = charToWChar(fileName);

	success = ilLoadImage(wFileName);

	if(!success)
	{
		error = ilGetError();
		fprintf(stderr, "Error: '%S'\n", iluErrorString(error));
		exit(1);
	}

	ILinfo imageInfo;
	iluGetImageInfo(&imageInfo);
	if(imageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		iluFlipImage();

	success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

	if(!success)
	{
		error = ilGetError();
		fprintf(stderr, "Error: '%S'\n", iluErrorString(error));
		exit(1);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 ilGetInteger(IL_IMAGE_FORMAT),
				 ilGetInteger(IL_IMAGE_WIDTH),
				 ilGetInteger(IL_IMAGE_HEIGHT),
				 0,
				 ilGetInteger(IL_IMAGE_FORMAT),
				 GL_UNSIGNED_BYTE,
				 ilGetData());

	ilDeleteImages(1, &imageID);

	return textureID;
}