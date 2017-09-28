#ifndef _HUMAN_
#define _HUMAN_

#include "enemy.h"

class Human : public Enemy {
private:
	Stats basestats = {
		140, //HP
		140, //MaxHP
		20,  //Atk
		20   //Def
	};
	Name thisName = {
		"Human", //Name
		'H'      //Symbol
	};

public:
	Human(Position pos, Level * thisLevel);
	~Human();

	//Drops 2 normal piles of gold
   // bool Attack(Character & target) override;
};

#endif
