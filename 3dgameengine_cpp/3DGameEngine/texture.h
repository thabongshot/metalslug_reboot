#ifndef _TEXTURE_H_
#define _TEXTURE_H_

class Texture
{
private:
	unsigned int id;

	static unsigned int loadTexture(const char *fileName);

public:
	Texture();

	Texture(const char *fileName);

	Texture(unsigned int id);

	void bind();

	unsigned int getID();
};

#endif