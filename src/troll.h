#ifndef _TROLL_
#define _TROLL_

#include "player.h"

class Troll : public Player {
private:
	Stats basestats = {
		120, //HP
		120, //MaxHP
		25,  //Atk
		15   //Def
	};
	Name thisName = {
		"Troll", //Name
		'@'      //Symbol
	};

	void AutoRegen();

public:
	Troll(Position pos); //Does nothing
	~Troll();
	bool TurnStart() override; //Call special effect

};

#endif
