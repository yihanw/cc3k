#include "merchant.h"

#include "position.h"
#include "stats.h"
#include "name.h"

#include "character.h"
#include "level.h"


#include "treasure.h"
#include "hoard.h"
#include <memory>
using namespace std;
Merchant::Merchant(Position pos, Level * thisLevel) : Enemy{ pos, thisLevel } {
	this->level = thisLevel;
	this->stats = basestats;
	this->name = thisName;
	this->isHostile = level->areMerchantsHostile();

}
Merchant::~Merchant() {
	if (!this->level->getWon()) {
		if (!level->areMerchantsHostile()) {
			std::cout << "You have murdered an innocent merchant. Merchants will now attack at will!" << std::endl;
			level->notifyMerchants();
		}
		Position pos = this->getPosition();

		std::shared_ptr<Treasure> treasure = std::make_shared <Treasure>(pos, HoardType::Merchant);
		this->level->DropItemAt(treasure, pos, false);

		std::cout << this->name.name << " has dropped a " << treasure->getName().name << std::endl;
	}
}

bool Merchant::TurnStart() {
	this->isHostile = level->areMerchantsHostile();
	return true;
}
//Becomes hostile to the player if a merchant was slayed,
//attacks within a one block radius; otherwise, stay
//neutral to all parties
bool Merchant::Attack(Character & target){
    if(getIsHostile()){
        if (this->hasHit()) {
            target.beStruckBy(*this);
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
    else{
        return false;
    }
}

bool Merchant::beStruckBy(Character & attacker){
    int damage = this->CalculateDamage(attacker.getStats(), this->getStats());
    this->stats.addHP(-damage);
    std::cout << attacker.getName().name << " dealt " << damage << " damage to " << this->getName().name << std::endl;
	if (!level->areMerchantsHostile()) {
		std::cout << "You have attacked an innocent merchant. Merchants will now attack at will!" << std::endl;
		level->notifyMerchants();
	}
    return true;
}
