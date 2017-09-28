#include "orc.h"

#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"

#include <iostream>

Orc::Orc(Position pos, Level * thisLevel) : Enemy{ pos, thisLevel } {
	this->stats = basestats;
	this->name = thisName;
	this->setGold(this->getRandomDefaultGoldValue());
}

Orc::~Orc() {}

//Does 50% more on goblins
bool Orc::Attack(Character & target){
	if (this->hasHit()) {
		if (target.getName().name == Predator) {
			this->DealExtraDamage(target);
		}
		else {
			target.beStruckBy(*this);
		}
		int TargetHP = target.getStats().HP;
		if (TargetHP <= 0) {
			this->addGold(target.getGold());
		}
	}
	else {
		std::cout << this->name.name << " has missed its attack!" << std::endl;
	}
	return true;
}

int Orc::calculateBonusDamage(int original) {
	return original + (original / 2);
}

void Orc::DealExtraDamage(Character & target)
{
	int damage = this->CalculateDamage(this->getStats(), target.getStats());
	int bonusDamage = calculateBonusDamage(damage);
	target.getStats().addHP(-bonusDamage);
    std::cout << this->name.name << " dealt " << damage << " damage to " << target.getName().name << std::endl;
	std::cout << this->name.name << " dealt " << (damage / 2) << " extra damage to " << target.getName().name << std::endl;

}
