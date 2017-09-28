#ifndef _HALFLING_
#define _HALFLING_

#include "enemy.h"

class Halfling : public Enemy {
private:
	Stats basestats = {
		100, //HP
		100, //MaxHP
		15,  //Atk
		20   //Def
	};
	Name thisName = {
		"Halfling", //Name
		'L'         //Symbol
	};

public:
	Halfling(Position pos, Level * thisLevel);
	~Halfling();

	bool beStruckBy(Character & attacker) override; // 50 % chance to cause the player to miss in combat
};

#endif
