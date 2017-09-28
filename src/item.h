#ifndef _ITEM_
#define _ITEM_

#include "position.h"
#include "name.h"


class Item {
protected:
	Position pos;
	Name name;

public:
	Item(Position pos);
	Position getPos(); // get the position of the item
	Name getName(); // get the name of the item
	void setPos(Position pos); // set position to pos	 
	virtual ~Item() = 0;
};

#endif
