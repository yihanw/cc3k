#ifndef  _TREASURE_
#define _TREASURE_

#include "item.h"
#include "hoard.h"


class Treasure : public Item {
	int amount;
	bool isAbleToPickUp = true;
	void setHoard(HoardType hoard); // sets the type of hoard
	
public:
	Treasure(Position pos, HoardType hoard);
	~Treasure();
	int getGold(); //returns amount
	void setIsAbleToPickUp(bool status); // set if the treasure is available to pick up based on the status
	bool getIsAbleToPickUp(); // get the status of the treasure if it is available to pick up
};

#endif // ! _TREASURE_

