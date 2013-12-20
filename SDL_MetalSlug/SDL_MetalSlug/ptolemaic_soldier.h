#ifndef PTOLEMAIC_SOLDIER_H
#define PTOLEMAIC_SOLDIER_H

#include "player.h"

class PtolemaicSoldier : public Player {
private:
	bool alarmed;

public:
	PtolemaicSoldier(std::vector<SDL_Surface*> sheets, 
					 std::vector<std::vector<SDL_Rect>> animClips,
					 std::vector<bool> loop,
					 int hp);
	~PtolemaicSoldier();

	void alarm();
};

#endif