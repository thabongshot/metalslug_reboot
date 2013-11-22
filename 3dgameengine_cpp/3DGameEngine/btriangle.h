#ifndef _BTRIANGLE_H_
#define _BTRIANGLE_H_

#include "mesh.h"

class bTriangle
{
private:
	Mesh *mesh;

public:
	bTriangle();

	void drawMesh();
};

#endif