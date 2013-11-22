#ifndef _SPRITE_2D_H_
#define _SPRITE_2D_H_

#include "object.h"

class Sprite2D : public Object
{
public:
	Sprite2D(const char *name);
	Sprite2D(const char *name, Transform *transform, Mesh *mesh);
};

#endif