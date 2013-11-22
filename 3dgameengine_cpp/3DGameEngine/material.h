#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "mymath.h"
#include "texture.h"

class Material
{
private:
	Texture texture;
	Texture normalTexture;
	Vector3f color;
	float specularIntensity;
	float specularPower;

public:
	Material(Texture texture, Texture normalTexture, Vector3f color, float specularIntensity, float specularPower);

	Texture *getTexture();

	void setTexture(Texture texture);

	Texture *getNormalTexture();

	void setNormalTexture(Texture normalTexture);

	Vector3f getColor();

	void setColor(Vector3f color);

	float getSpecularIntensity();

	void setSpecularIntensity(float specularIntensity);

	float getSpecularPower();

	void setSpecularPower(float specularPower);
};

#endif