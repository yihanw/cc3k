#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"
#include "goblin.h"

#include <iostream>

Goblin::Goblin(Position pos) : Player{ pos } {
	this->baseStats = basestats;
	this->stats = basestats;
	this->name = thisName;
}

Goblin::~Goblin() {}

bool Goblin::Attack(Character & target) {
	target.beStruckBy(*this);
	int TargetHP = target.getStats().HP;
	if (TargetHP <= 0) {
		ExtraGold();
		this->addGold(target.getGold());
	}
	return true;
}

//Steal 5 gold if enemy slain
void Goblin::ExtraGold() {
	this->addGold(5);
	std::cout << this->name.name << " gains an extra 5 gold from its special effect!" << std::endl;

}

