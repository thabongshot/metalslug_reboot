#include "material.h"

Material::Material(Texture texture, Texture normalTexture, Vector3f color, float specularIntensity, float specularPower)
{
	this->texture = texture;
	this->normalTexture = normalTexture;
	this->color = color;
	this->specularIntensity = specularIntensity;
	this->specularPower = specularPower;
}

Texture *Material::getTexture()
{
	return &texture;
}

Texture *Material::getNormalTexture()
{
	return &normalTexture;
}

void Material::setTexture(Texture texture)
{
	this->texture = texture;
}

void Material::setNormalTexture(Texture normalTexture)
{
	this->normalTexture = normalTexture;
}

Vector3f Material::getColor()
{
	return color;
}

void Material::setColor(Vector3f color)
{
	this->color = color;
}

float Material::getSpecularIntensity()
{
	return specularIntensity;
}

void Material::setSpecularIntensity(float specularIntensity)
{
	this->specularIntensity = specularIntensity;
}

float Material::getSpecularPower()
{
	return specularPower;
}

void Material::setSpecularPower(float specularPower)
{
	this->specularPower = specularPower;
}