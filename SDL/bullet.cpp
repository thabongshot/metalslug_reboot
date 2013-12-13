#include "bullet.h"

Bullet::Bullet(int x, int y, int moveSpeed, std::vector<Animation*> animations) : Sprite(x, y, moveSpeed, animations) {
	
}

Bullet::Bullet(const Bullet &other) : Sprite(other.x, other.y, other.moveSpeed, other.animations) {
	
}

Bullet::~Bullet() {

}

void Bullet::Update(Timer *timer) {
	if(!active) return;

	if(x > 800) {
		active = false;
	}
	else {
		x += (xDir * timer->GetDeltaTime() / 10) * moveSpeed;
		y += (yDir * timer->GetDeltaTime() / 10) * moveSpeed;
	}

	if(currAnimation)
		currAnimation->Update(timer);
}