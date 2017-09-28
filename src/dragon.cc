#include "dragon.h"

#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"

//Stationary and always guards a treasure gold

Dragon::Dragon(Position pos, Level * thisLevel) : Enemy{ pos, thisLevel } {
	this->stats = basestats;
	this->name = thisName;
	this->isHostile = false;
}
Dragon::~Dragon() {}

bool Dragon::Move(Position pos) {
	return false;
}

