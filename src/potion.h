#ifndef _POTION_
#define _POTION_

#include "item.h"
#include "stats.h"

#include "potiontypes.h"

class Potion : public Item {
private:
	//Name name;
//	int amount;
	Stats buff;
	void makeRandomPotion(); // randomly generate the potion
	void AssignThisPotion(PotionType pot); // assigns the potion to potion type, pot
    
public:
	Potion(Position pos);
	Potion(Position pos, PotionType pot); //Indicates amount
	~Potion();

	//void Use(Stats & playerStats); //Type of potion based on name

	Stats getStats() const;
	void setStats(Stats stats);

};

Stats  operator+ (const Potion & can, Stats & stat);
Stats  operator+ ( Stats & stat, const Potion & can) ;

#endif
