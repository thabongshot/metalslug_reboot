#ifndef _BULLET_H_
#define _BULLET_H_

#include "sprite.h"

class Bullet : public Sprite {
public:
	Bullet(int x, int y, int moveSpeed, std::vector<Animation*> animations);
	Bullet(const Bullet &other);
	~Bullet();

	virtual void Update(Timer *timer);
};

#endif