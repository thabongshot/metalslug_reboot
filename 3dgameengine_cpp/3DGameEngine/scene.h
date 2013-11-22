#ifndef _SCENE_H_
#define _SCENE_H_

#include "object.h"

#include <vector>

class Scene
{
private:
	static std::vector<Object*> objects;

public:
	Scene();

	static void addObject(const char*, Object*);

	static Object *getObject(const char*);

	void input();

	void update();

	void render();
};

#endif