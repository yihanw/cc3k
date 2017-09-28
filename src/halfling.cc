#include "halfling.h"

#include "position.h"
#include "stats.h"
#include "name.h"



#include <iostream>


//#include "character.h"
//#include "enemy.h"

#include "myrand.h"

Halfling::Halfling(Position pos, Level * thisLevel) : Enemy{ pos, thisLevel } {
	this->setGold(this->getRandomDefaultGoldValue());
	this->stats = basestats;
	this->name = thisName;

}

Halfling::~Halfling() {}

// 50 % chance to cause the player to miss in combat
bool Halfling::beStruckBy(Character & attacker) {
	Random r;
	//int hit = r.Range(0, 1);
    int hit = r.Range(1, 2);



	if (hit == 1) {
		int damage = this->CalculateDamage(attacker.getStats(), this->getStats());
		this->stats.addHP(-damage);
		std::cout << attacker.getName().name << " dealt " << damage << " damage to " << this->getName().name << std::endl;
	}
	else {
		std::cout << attacker.getName().name <<  " missed!" << std::endl;
	}
	return true;
}
