#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"
#include "drow.h"
#include "potion.h"

#include <iostream>
using namespace std;

Drow::Drow(Position pos) : Player{ pos } {
	this->baseStats = basestats;
	this->stats = basestats;
	this->name = thisName;
}

Drow::~Drow() {}

//potions x1.5
void Drow::usePotion(Potion & pot) {
    cout << "Original: " << this->stats.HP << " " << this->stats.Atk << " " << this->stats.Def << endl;
    
	pot.setStats(pot.getStats() * 1.5f); //Note it is 2 for now because ints
	this->stats = this->stats + pot;
	std::cout << this->name.name << " gains extra status effects!" << std::endl;
    
	this->stats.CheckNoBelowZero();
    
    cout << "After: " << this->stats.HP << " " << this->stats.Atk << " " << this->stats.Def << endl;
}

