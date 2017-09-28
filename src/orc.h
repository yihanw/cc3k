#ifndef _ORC_
#define _ORC_

#include "enemy.h"

class Orc : public Enemy {
private:
	Stats basestats = {
		180, //HP
		180, //MaxHP
		30,  //Atk
		25   //Def
	};
	Name thisName = {
		"Orc", //Name
		'O'    //Symbol
	};

	const std::string Predator = "Goblin";
	void DealExtraDamage(Character & target); // does extra damage to target
	int calculateBonusDamage(int original); // calculate the extra damage

public:
	Orc(Position pos, Level * thisLevel);
	~Orc();
	bool Attack(Character & target) override; // Gets two attacks on all Heroes except for drow and does 50% more on goblins
};

#endif
