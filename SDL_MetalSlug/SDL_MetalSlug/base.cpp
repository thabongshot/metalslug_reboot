#include "base.h"

bool BaseClass::collision(SDL_Rect *rec1, SDL_Rect *rec2) {
	if(rec1->y >= rec2->y + rec2->h)
		return 0;
	if(rec1->x >= rec2->x + rec2->w)
		return 0;
	if(rec1->y + rec1->h <= rec2->y)
		return 0;
	if(rec1->x + rec1->w <= rec2->x)
		return 0;
	return 1;
}