#include "ptolemaic_soldier.h"

PtolemaicSoldier::PtolemaicSoldier(std::vector<SDL_Surface*> sheets, std::vector<std::vector<SDL_Rect>> animClips, std::vector<bool> loop, int hp) : Player(sheets, animClips, loop, hp){
	lastDirection = -1;

	alarmed = false;
}

PtolemaicSoldier::~PtolemaicSoldier() {

}

void PtolemaicSoldier::alarm() {
	if(!alarmed)
		alarmed = true;
}