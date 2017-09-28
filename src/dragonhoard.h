#ifndef _DRAGONHOARD_
#define _DRAGONHOARD_

#include "treasure.h"
#include <memory>
class Dragon;

class DragonHoard : public Treasure {
	std::shared_ptr<Dragon> dragon;
    
public:
	DragonHoard(Position pos, HoardType hoard, std::shared_ptr<Dragon> drago);

	void notifyDragon(); // set dragon to be hostile
	void unNotifyDragon(); // set dragon to be unhostile

	bool isDragonAlive(); // check if dragon is alive
};

#endif
