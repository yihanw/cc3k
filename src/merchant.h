#ifndef _MERCHANT_
#define _MERCHANT_

#include "enemy.h"

class Merchant : public Enemy {
private:
	Stats basestats = {
		30, //HP
		30, //MaxHP
		70, //Atk
		5   //Def
	};
	Name thisName = {
		"Merchant", //Name
		'M'     //Symbol
	};
     bool TurnStart() override;
    
public:
	Merchant(Position pos, Level * thisLevel);
	~Merchant();
	
 	bool Attack(Character & target) override; //Becomes hostile to the player if a merchant was slayed,
											  //attacks within a one block radius; otherwise, stay
											  //neutral to all parties
	bool beStruckBy(Character & attacker) override;
};

#endif
