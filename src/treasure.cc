#include "treasure.h"

Treasure::Treasure(Position pos, HoardType hoard) : Item{ pos } {
	setHoard(hoard);
	this->name.symbol = 'G';

	if (hoard == HoardType::Small) {
		this->name.name = "Small Hoard";
	}
	else if (hoard == HoardType::Normal) {
		this->name.name = "Normal Hoard";
	}
	else if (hoard == HoardType::Merchant) {
		this->name.name = "Merchant Hoard";
	}
	else if (hoard == HoardType::Dragon) {
		this->name.name = "Dragon hoard";
	}


}

Treasure::~Treasure() {}

//returns amount
int Treasure::getGold() {
	return this->amount; //PLACEHOLDER
}

void Treasure::setIsAbleToPickUp(bool status) {
	this->isAbleToPickUp = status;
}

bool Treasure::getIsAbleToPickUp() {
	return this->isAbleToPickUp;
}

void Treasure::setHoard(HoardType hoard) {
	int hoardamount = static_cast<int>(hoard);
	this->amount = hoardamount;
}


