#ifndef _GOBLIN_
#define _GOBLIN_

#include "player.h"
class Goblin : public Player {
private:
	Stats basestats = {
		110, //HP
		110, //MaxHP
		15,  //Atk
		20   //Def
	};
    
	Name thisName = {
		"Goblin", //Name
		'@'       //Symbol
	};

	void ExtraGold(); //Steal 5 gold if enemy slain

public:
	Goblin(Position pos); //Does nothing
	~Goblin();

	bool Attack(Character & target) override; // attacks the target

};

#endif
