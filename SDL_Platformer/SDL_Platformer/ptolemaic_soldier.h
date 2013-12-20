#ifndef PTOLEMAIC_SOLDIER_H
#define PTOLEMAIC_SOLDIER_H

#include "player.h"

class PtolemaicSoldier : public Player {
public:
	PtolemaicSoldier(std::vector<SDL_Surface*> sheets, 
					 std::vector<std::vector<SDL_Rect>> animClips,
					 std::vector<bool> loop,
					 std::vector<double> animSpeed,
					 int hp);
	~PtolemaicSoldier();

	virtual void alarm(Player *target);

	virtual void ceaseAlarm();
};

#endif