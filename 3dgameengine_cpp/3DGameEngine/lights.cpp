#include "lights.h"

BaseLight::BaseLight(Vector3f color, float intensity) : Light()
{
	this->color = color;
	this->intensity = intensity;
}

DirectionalLight::DirectionalLight(BaseLight baseLight, Vector3f direction) : Light()
{
	this->baseLight = baseLight;
	this->direction = direction.normalized();
}

PointLight::PointLight(BaseLight baseLight, Vector3f position, float constant, float linear, float exponent, float range) : Light()
{
	this->baseLight = baseLight;
	this->position = position;

	attenuation.constant = constant;
	attenuation.linear = linear;
	attenuation.exponent = exponent;

	this->range = range;
}

SpotLight::SpotLight(PointLight pointLight, Vector3f direction, float cutOff) : Light()
{
	this->pointLight = pointLight;
	this->direction = direction.normalized();
	this->cutOff = cutOff;
}