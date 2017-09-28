#ifndef _SHADE_
#define _SHADE_

#include "player.h"

class Shade : public Player{

private:
	Stats basestats = {
		125, //HP
		125, //MaxHP
		25,  //Atk
		25   //Def
	};
	Name thisName = {
		"Shade", //Name
		'@'      //Symbol
	};

public:
	Shade(Position pos); //Do nothing
	~Shade();


};

#endif
