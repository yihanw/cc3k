#ifndef _ELF_
#define _ELF_

#include "enemy.h"

class Elf : public Enemy {
private:
	Stats basestats = {
		140, //HP
		140, //MaxHP
		30,  //Atk
		10   //Def
	};
	Name thisName = {
		"Elf", //Name
		'E'    //Symbol
	};

	const int initNumberOfAttacks = 2;
	const std::string Nemesis = "Drow";

public:
	Elf(Position pos, Level * thisLevel);
	~Elf();
	bool Attack(Character & target) override; //Gets two attacks on all Heroes except for drow
};

#endif
