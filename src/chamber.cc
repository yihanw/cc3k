#include "chamber.h"
#include "name.h"
#include "display.h"
#include "position.h"
#include "myrand.h"
#include <stdlib.h>

#include <iostream>
#include <string>
using namespace std;

Chamber::Chamber(int chamberNum, Level * lev) :chamberNum{ chamberNum }, level{ lev } {
	//top left corner as (0,0)
	if (chamberNum == 0) { //top left, rectangle
		startRow = 2;
		startCol = 2;
		lengthRow = 26;
		lengthCol = 4;
	}
	else if (chamberNum == 1) { //bottom left, rectangle
		startRow = 14;
		startCol = 3;
		lengthRow = 21;
		lengthCol = 7;
	}
	else if (chamberNum == 2) { //top right, irregular
		startRow = 2;
		startCol = 38;
		lengthRow = 37;
		lengthCol = 10;
	}
	else if (chamberNum == 3) { //middle, rectangle
		startRow = 9;
		startCol = 37;
		lengthRow = 12;
		lengthCol = 3;
	}
	else if (chamberNum == 4) { //bottom right, irregular
		startRow = 15;
		startCol = 36;
		lengthRow = 39;
		lengthCol = 6;
	}
	else {}
	//level->getDisplay()->setDisplayAtPos(Position{ startRow, startCol }, 'O'); //0
	//level->getDisplay()->setDisplayAtPos(Position{ startRow + lengthCol, startCol + lengthRow }, 'L'); //0

}

Chamber::~Chamber() {}

int Chamber::getChamberNum() {
	return chamberNum;
}

int Chamber::getStartRow() {
	return startRow;
}

int Chamber::getStartCol() {
	return startCol;
}

int Chamber::getLengthRow() {
	return lengthRow;
}

int Chamber::getLengthCol() {
	return lengthCol;
}

Position Chamber::randomGenerate(int levelIndex) {
	Position pos{ 0,0 };
	int tries = 0;
	int maximumTries = 1000;
	while (true) {

		Random r;
		pos.x = r.Range(startRow + 1, startRow + lengthCol + 1);
		pos.y = r.Range(startCol + 1, startCol + lengthRow + 1);

		if (withinChamber(pos) && isFloorTile(pos, levelIndex)) break;

		tries++;
		if (tries >= maximumTries) {
			cout << "Something went wrong with randomGenerate!" << endl;
			break;
		}
	}

	return pos;
}



bool Chamber::isFloorTile(Position pos, int levelIndex) {
	char tile = level->getMaps()[levelIndex][pos.x][pos.y];
	if (tile == '.') {
		return true;
	}
	else {
		return false;
	}
}

bool Chamber::withinChamber(Position pos) {
	int r = pos.x;
	int c = pos.y;
	int maxRowLength = startRow + lengthCol;
	int maxColLength = startCol + lengthRow;
	// cout << "withinChamber: pos.x: " << pos.x << " pos.y: " << pos.y << endl;
	if (chamberNum == 0 || chamberNum == 1 || chamberNum == 3) {
		if ((r>startRow && r <= maxRowLength) && (c>startCol && c <= maxColLength)) {
			//        cout << "is in chamber" << endl << endl;
			return true;
		}
	}
	else if (chamberNum == 2) {
		int breakpoint1 = 61, breakpoint2 = 69, breakpoint3 = 73;
		if (((r>startRow && r <= 4) && (c>startCol && c <= breakpoint1)) ||
			(r == 5 && (c>startCol && c <= breakpoint2)) ||
			(r == 6 && (c>startCol && c <= breakpoint3)) ||
			((r >= 7 && r <= maxRowLength) && (c >= breakpoint1 && c <= maxColLength))) {
			return true;
		}
	}
	else if (chamberNum == 4) {
		int breakpoint1 = startRow + 3, breakpoint2 = 65;
		if (((r>startRow && r <= breakpoint1) && (c >= breakpoint2 && c <= maxColLength)) ||
			((r>breakpoint1 && r <= maxRowLength) && (c >= startCol && c <= maxColLength))) {
			return true;
		}
	}
	// cout << "is not in chamber" << endl << endl;
	return false;
}
