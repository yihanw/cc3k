#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"
#include "shade.h"

Shade::Shade(Position pos) : Player{ pos } {
	this->baseStats = basestats;
	this->stats = basestats;
	this->name = thisName;
}

Shade::~Shade() {}

//All functions are default
