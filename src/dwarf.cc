
#include "dwarf.h"

#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"

Dwarf::Dwarf(Position pos, Level * thisLevel) : Enemy{ pos, thisLevel } {
	this->setGold( this->getRandomDefaultGoldValue());
	this->stats = basestats;
	this->name = thisName;
}

Dwarf::~Dwarf() {}


