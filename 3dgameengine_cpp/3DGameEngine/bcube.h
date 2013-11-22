#ifndef _BCUBE_H_
#define _BCUBE_H_

#include "mesh.h"

class bCube
{
private:
	Mesh *mesh;

public:
	bCube();

	void drawMesh();
};

#endif