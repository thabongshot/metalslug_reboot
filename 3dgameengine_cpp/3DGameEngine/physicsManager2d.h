#ifndef _PHYSICS_MANAGER_2D_H_
#define _PHYSICS_MANAGER_2D_H_

#include <Box2D\Box2D.h>
#include <set>

class PhysicsManager2D
{
private:
	static PhysicsManager2D *pInstance;

	b2World *pWorld;

	PhysicsManager2D();

public:
	static PhysicsManager2D *getInstance();

	b2Body *createRectangleBody(b2BodyType bodyType, float x, float y, float width, float height, float originX, float originY, float angle);

	void update(float deltaTime);
};

#endif