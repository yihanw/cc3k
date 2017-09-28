#ifndef _CHARACTER_
#define _CHARACTER_

#include "stats.h"
#include "position.h"
#include "name.h"

#include <memory>
class Level;

class Character {
protected:
	Stats stats;
	Position position;
	Name name;

	int CalculateDamage(Stats attacker, Stats defender); // calculate the damage received by defender by attacker
	int goldValue = 0;

	Level * level;

public:
	Character(Position pos);
	virtual ~Character() = 0;


	virtual bool Move(Position pos); // move to Position, pos
	virtual bool Attack(Character & target); // attacks the target
	virtual bool beStruckBy(Character & attacker); // be struck by attacker
	virtual bool TurnStart(); // turn start for character

	//Getters/Setters:

	Stats getStats();
	void setStats(Stats stat);

	Position getPosition();
	void setPosition(Position pos);

	Name getName();
	void setName(Name nam);

	int getGold();
	void setGold(int set);
	void addGold(int add);
};

#endif
