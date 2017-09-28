#ifndef _PLAYER_
#define _PLAYER_

#include "character.h"
class Potion;

class Player : public Character{
protected:
	//int goldAmount;
	Stats baseStats;

public:
	//int getGold();
//	void addGold( int amount);
	Player(Position pos);
	virtual ~Player() = 0;

	virtual void usePotion(Potion & pot);

	Stats getBaseStats();
	void revertToBaseStats();

};

#endif
