#include "player.h"

#include "input.h"

Player::Player(int x, int y, int hw, int hh, int moveSpeed, std::vector<Animation*> animations) : Sprite(x, y, hw, hh, moveSpeed, animations) {
	body->SetUserData(this);
}

void Player::Input(SDL_Event *e) {
	xDir = 0;
	yDir = 0;

	switch(e->key.keysym.sym) {
	case SDLK_LEFT:
		if(e->key.state == SDL_PRESSED)
			xDir = -1;
		break;
	case SDLK_RIGHT:
		if(e->key.state == SDL_PRESSED)
			xDir = 1;
		break;
	};
}

void Player::Update(Timer *timer) {
	if(!active) return;

	if(currAnimation)
		currAnimation->Update(timer);

	/*
	if(getAnimation(2)->finished) {
		jumping = false;
		yDir = 0;
	}

	if(jumping && !getAnimation(2)->finished) {
		SetCurrAnimation(2);
	}
	else if(xDir == -1) {
		// set left animation
		SetCurrAnimation(1);
	}
	else if(xDir == 1) {
		// set right animation
		SetCurrAnimation(1);
	}
	else {
		SetCurrAnimation(0);
	}

	x += xDir * (timer->GetDeltaTime() / 10) * moveSpeed;
	y += yDir * (timer->GetDeltaTime() / 10) * moveSpeed;
	*/

	body->SetLinearVelocity(b2Vec2(xDir * moveSpeed, yDir * moveSpeed));

	body->SetLinearVelocity(body->GetLinearVelocity() + b2Vec2(0, 200));
}

void Player::Render(SDL_Renderer *renderer, int camX, int camY) {
	if(!active) return;

	if(currAnimation)
		currAnimation->Render(body->GetPosition().x, body->GetPosition().y, camX, camY, renderer);
}