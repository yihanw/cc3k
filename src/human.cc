#include "human.h"

#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"
#include "level.h"

#include "treasure.h"
#include "hoard.h"

#include <memory>
using namespace std;

//Drops 2 normal piles of gold
Human::Human(Position pos, Level * thisLevel) : Enemy{ pos, thisLevel } {
	this->level = thisLevel;
	this->stats = basestats;
	this->name = thisName;
}

Human::~Human() {
	if (!this->level->getWon()) {
	Position pos = this->getPosition();
	const int goldDropped = 2;
	for (int i = 0; i < goldDropped; i++) {
		shared_ptr<Treasure> treasure = make_shared <Treasure>(pos, HoardType::Normal);
		this->level->DropItemAt(treasure, pos, true);
			std::cout << this->name.name << " has dropped a " << treasure->getName().name << std::endl;
		}
	}
}


