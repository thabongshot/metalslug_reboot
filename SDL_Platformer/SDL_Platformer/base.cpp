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

int BaseClass::calculateDistance(SDL_Rect *rect1, SDL_Rect *rect2) {
	int dx = rect2->x - rect1->x;
	int dy = rect2->y - rect1->y;

	return (dx * dx + dy * dy);
}