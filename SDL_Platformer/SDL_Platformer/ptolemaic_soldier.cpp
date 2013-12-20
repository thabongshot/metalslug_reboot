#include "ptolemaic_soldier.h"

PtolemaicSoldier::PtolemaicSoldier(std::vector<SDL_Surface*> sheets, std::vector<std::vector<SDL_Rect>> animClips, std::vector<bool> loop, std::vector<double> animSpeed, int hp) : Player(sheets, animClips, loop, animSpeed, hp){
	lastDirection = -1;

	alarmed = false;
}

PtolemaicSoldier::~PtolemaicSoldier() {

}

void PtolemaicSoldier::alarm(Player *target) {
	if(!alarmed) {
		alarmed = true;

		if(box.x > target->getRect()->x) {
			setLastDirection(-1);
			setXVel(-2);
			setCurrAnim(3);
		}
		else {
			setLastDirection(1);
			setXVel(2);
			setCurrAnim(2);
		}
	}
}

void PtolemaicSoldier::ceaseAlarm() {
	if(alarmed) {
		alarmed = false;

		if(lastDirection == -1) {
			setCurrAnim(1);
			setXVel(0);
		}
		else {
			setCurrAnim(0);
			setXVel(0);
		}
	}
}