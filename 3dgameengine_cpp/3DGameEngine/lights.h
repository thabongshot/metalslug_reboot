#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include "mymath.h"

struct Light
{
	Light()
	{

	}
};

struct BaseLight : public Light
{
	Vector3f color;
	float intensity;

	BaseLight() : Light()
	{
		color = Vector3f(0, 0, 0);
		intensity = 0;
	}

	BaseLight(Vector3f color, float intensity);
};

struct DirectionalLight : public Light
{
	BaseLight baseLight;
	Vector3f direction;

	DirectionalLight() : Light()
	{
		baseLight = BaseLight();
		direction = Vector3f(0, 1, 1);
	}

	DirectionalLight(BaseLight baseLight, Vector3f direction);
};

struct PointLight : public Light
{
	BaseLight baseLight;
	Vector3f position;

	struct 
	{
		float constant;
		float linear;
		float exponent;
	} attenuation;

	float range;

	PointLight() : Light()
	{
		baseLight = BaseLight();
		position = Vector3f();

		attenuation.constant = 0;
		attenuation.linear = 0;
		attenuation.exponent = 0;

		range = 0;
	}

	PointLight(BaseLight baseLight, Vector3f position, float constant, float linear, float exponent, float range);
};

struct SpotLight : public Light
{
	PointLight pointLight;
	Vector3f direction;
	float cutOff;

	SpotLight() : Light()
	{
		pointLight = PointLight();
		direction = Vector3f(1, -1, 1);
		cutOff = 0;
	}

	SpotLight(PointLight pointLight, Vector3f direction, float cutOff);
};

#endif