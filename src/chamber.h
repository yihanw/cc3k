#ifndef _CHAMBER_
#define _CHAMBER_

#include <memory>
#include "level.h"

class Level;
class Display;
struct Name;
struct Position;

class Chamber{
private:
	int chamberNum = 0;
	int startRow = 0;
	int startCol = 0;
	int lengthRow = 0;
	int lengthCol = 0;
	Level * level;
	std::shared_ptr<Display> theDisplay;

public:
	Chamber(int chamberNum, Level * lev);
	~Chamber();
	int getChamberNum(); // get the chamber number
	int getStartRow();   // get the row of the start position of the chamber
	int getStartCol();   // get the column of the start position of the chamber
	int getLengthRow();  // get the length of the row of the chamber
	int getLengthCol();  // get the length of the coloum of the chamber
	Position randomGenerate(int levelIndex);  // randomly generate a valid postion
    bool isFloorTile(Position pos, int levelIndex);  // check if a floor tile is valid
	bool withinChamber(Position pos);  // check if a position is within chamber
};

#endif
