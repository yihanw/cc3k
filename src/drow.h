#ifndef _DROW_
#define _DROW_

#include "player.h"
//Potions x1.5
class Drow : public Player {
private:
	Stats basestats = {
		150, //HP
		150, //MaxHP
		25,  //Atk
		15   //Def
	};
	Name thisName = {
		"Drow", //Name
		'@'     //Symbol
	};

public:
	Drow(Position pos);
	~Drow();

	void usePotion(Potion & pot) override; // get magnify of 1.5 effects when using potion

};

#endif
