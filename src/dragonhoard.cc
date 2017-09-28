#include "dragonhoard.h"
#include "dragon.h"

DragonHoard::DragonHoard(Position pos, HoardType hoard, std::shared_ptr<Dragon> drago) : Treasure{ pos, hoard } {
	this->setIsAbleToPickUp(false);
	this->dragon = drago;

}

void DragonHoard::notifyDragon() {
	this->dragon->setIsHostile(true);
}

void DragonHoard::unNotifyDragon() {
	this->dragon->setIsHostile(false);
}

bool DragonHoard::isDragonAlive() {
    if(this->dragon->getStats().HP>0){
        return true;
    }
    else{
        return false;
    }
	//return !(this->dragon == nullptr);
}
