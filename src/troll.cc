#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"
#include "troll.h"

#include <iostream>

Troll::Troll(Position pos) : Player{ pos } {
	this->baseStats = basestats;
	this->stats = basestats;
	this->name = thisName;
} //Does nothing
Troll::~Troll() {}


//Call special effect
bool Troll::TurnStart() {
	AutoRegen();
	return true;
}

//Regain 5HP
void Troll::AutoRegen() {
	if (this->stats.HP != this->stats.MaxHP) {
		this->stats.addHP(5);
		std::cout << this->name.name << " regenerates 5 HP!" << std::endl;
	}
}
