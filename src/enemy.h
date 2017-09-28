#ifndef _ENEMY_
#define _ENEMY_

#include "character.h"

class Enemy : public Character{
protected:
	//int goldAmount;
	bool isHostile;

	bool hasHit();  // Enemies have a 50% chance of hitting

	int getRandomDefaultGoldValue();


public:
	//void getGold();
	Enemy(Position pos, Level * thisLevel);
	virtual ~Enemy() = 0;
	bool getIsHostile(); // get the hostile status of the enemy
	void setIsHostile(bool status); // set the hostile by given status

	//Note that enemy movement is dictated by level - because you need to know if wall
	virtual bool Attack(Character & target); //Enemies have a 50% chance of missing
};

#endif
