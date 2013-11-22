#include "object.h"

#include "lua_backend.h"

#include <string.h>

Object::Object(const char *name)
{
	this->name = name;
	transform = new Transform();
	mesh = new Mesh();
}

Object::Object(const char *name, Transform *transform, Mesh *mesh)
{
	this->name = name;
	this->transform = transform;
	this->mesh = mesh;
}

Transform *Object::getTransform()
{
	return transform;
}

Mesh *Object::getMesh()
{
	return mesh;
}

const char *Object::getName()
{
	return name;
}

void Object::setTransform(Transform *transform)
{
	this->transform = transform;
}

void Object::setMesh(Mesh *mesh)
{
	this->mesh = mesh;
}

void Object::setName(const char *name)
{
	this->name = name;
}

void Object::addComponent(ObjectComponent *component)
{
	components.push_back(component);
}

void Object::printObject()
{
	printf("Hello I am %s.\n", name);
}

ScriptComponent::ScriptComponent(Object *parent, const char *script_fileName) : ObjectComponent(parent)
{
	this->script_fileName = script_fileName;
}

void ScriptComponent::attachScript(const char *script_fileName)
{
	this->script_fileName = script_fileName;
}

const char *ScriptComponent::getScript()
{
	return script_fileName;
}

void ScriptComponent::update()
{
	if(strcmp(script_fileName, "N/A") != 0)
		lua_exec_update(script_fileName);
}