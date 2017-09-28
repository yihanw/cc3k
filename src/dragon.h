#ifndef _DRAGON_
#define _DRAGON_

#include "enemy.h"
class Treasure;

class Dragon : public Enemy {
private:
	std::shared_ptr<Treasure>  hoard;

	Stats basestats = {
		150,  //HP
		150,  //MaxHP
		20,   //Atk
		20    //Def
	};
	Name thisName = {
		"Dragon", //Name
		'D'       //Symbol
	};

public:
	Dragon(Position pos, Level * thisLevel);
	~Dragon();
	bool Move(Position pos) override;
	//Stationary and always guards a treasure gold

};

#endif
