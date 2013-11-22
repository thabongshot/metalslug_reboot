#ifndef _BPLANE_H_
#define _BPLANE_H_

#include "mesh.h"

class bPlane
{
private:
	Mesh *mesh;

public:
	bPlane();

	void drawMesh();
};

#endif