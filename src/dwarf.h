#ifndef _DWARF_
#define _DWARF_

#include "enemy.h"

class Dwarf : public Enemy {
private:
	Stats basestats = {
		100, //HP
		100, //MaxHP
		20,  //Atk
		30   //Def
	};
	Name thisName = {
		"Dwarf", //Name
		'W'      //Symbol
	};

public:
	Dwarf(Position pos, Level * thisLevel);
	~Dwarf();
	//Make vampires lose 5HP (nothing really required on this end)
};

#endif
