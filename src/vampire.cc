#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"
#include "vampire.h"

#include <string>
using namespace std;
#include <iostream>

//Sets Maximum health to INT_MAX
Vampire::Vampire(Position pos) : Player{ pos } {
	this->baseStats = basestats;
	this->stats = basestats;
	this->name = thisName;

}

Vampire::~Vampire() {}

//Gains 5 HP every attack
bool Vampire::Attack(Character & target) {
	target.beStruckBy(*this);

	string name = target.getName().name;

	if (name != Nemesis) {
		LifeSteal();
	}
	else {
		Allergies();
	}

	int TargetHP = target.getStats().HP;
	if (TargetHP <= 0) {
		this->addGold(target.getGold());
	}
	return true;
}


//No maximum health; Gains 5 HP every attack
void Vampire::LifeSteal() {
	this->stats.addHP(this->VampireDrainAmount);
	std::cout << this->name.name << " stole 5 HP!" << std::endl;
}

void Vampire::Allergies() {
	this->stats.addHP(-this->VampireDrainAmount);
	std::cout << this->name.name << " loses 5 HP due to allergies!" << std::endl;
}

