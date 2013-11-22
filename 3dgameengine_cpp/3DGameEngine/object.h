#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "mesh.h"

extern "C"
{
#include "lua5.1\include\lua.h"
#include "lua5.1\include\lualib.h"
#include "lua5.1\include\lauxlib.h"
}

#include <vector>

typedef class Object *pObject;

class ObjectComponent
{
public:
	Object *parent;

	ObjectComponent(Object *parent)
	{
		this->parent = parent;
	}

	virtual void update()
	{

	}
};

class ScriptComponent : public ObjectComponent
{
private:
	const char *script_fileName;

public:
	ScriptComponent(Object *parent) : ObjectComponent(parent)
	{
		script_fileName = "N/A";
	}

	ScriptComponent(Object *parent, const char *script_fileName);

	void attachScript(const char *script_fileName);

	const char *getScript();

	virtual void update();
};

class Object
{
protected:
	const char *name;
	Transform *transform;
	Mesh *mesh;
	std::vector<ObjectComponent*> components;

public:
	Object(const char *name);
	Object(const char *name, Transform *transform, Mesh *mesh);

	Transform *getTransform();
	Mesh *getMesh();
	const char *getName();

	void setTransform(Transform *transform);
	void setMesh(Mesh *mesh);
	void setName(const char *name);

	void addComponent(ObjectComponent *component);

	virtual void update()
	{
		for(unsigned int i = 0; i < components.size(); i++)
		{
			ObjectComponent *pComp = components.at(i);

			pComp->update();
		}
	}

	virtual void draw()
	{
		if(mesh && transform)
			mesh->drawMesh(transform);
	}

	void printObject();
};

#endif