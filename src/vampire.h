#ifndef _VAMPIRE_
#define _VAMPIRE_

#include "player.h"
#include "climits"

class Vampire : public Player {
private:
	Stats basestats = {
		50,      //HP
		INT_MAX, //MaxHP
		25,      //Atk
		25       //Def
	};
	Name thisName = {
		"Vampire", //Name
		'@'        //Symbol
	};

	const int VampireDrainAmount = 5;
	const std::string Nemesis = "Dwarf";

	void LifeSteal();
	void Allergies();

public:
	Vampire(Position pos); //Sets Maximum health to INT_MAX
	~Vampire();
	bool Attack(Character & target) override; // attacks the target


};

#endif
