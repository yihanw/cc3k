#include "elf.h"

#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"

#include <iostream>

Elf::Elf(Position pos, Level * thisLevel) : Enemy{ pos, thisLevel } {
	this->setGold(this->getRandomDefaultGoldValue());
	this->stats = basestats;
	this->name = thisName;
}

Elf::~Elf() {}

//Gets two attacks on all Heroes except for drow
bool Elf::Attack(Character & target) {
	int NumOfAttacks = initNumberOfAttacks;

	if (target.getName().name == Nemesis) {
		NumOfAttacks--;
	}

	for (int i = 0; i < NumOfAttacks; i++) {
		if (this->hasHit()) {
			target.beStruckBy(*this);
			int TargetHP = target.getStats().HP;
			if (TargetHP <= 0) {
				this->addGold(target.getGold());
				return true;
			}
		}
		else {
			std::cout << this->name.name << " has missed its attack!" << std::endl;
		}

	}
	return true;
}

