#include "display.h"
#include <vector>
using namespace std;
#include "position.h"

#include <iostream>
using namespace std;

Display::Display() {
//Initialized in setFloor function

}
Display::~Display() {}

void Display::setDisplayRow(vector<char> row) {
	this->theDisplay.emplace_back(row);
}

void Display::setDisplayAtPos(Position pos, char rep) {
	if (pos.x < 0 || pos.x >= this->getNumRows()|| pos.y < 0 || pos.y >= this->getNumCols()) {
		cout << "BAD SET DISPLAY" << endl;
		return;
	}

	this->theDisplay[pos.x][pos.y] = rep;
}

char Display::getDisplayAtPos(Position pos) {
	if (pos.x < 0 || pos.x >= this->getNumRows() || pos.y < 0 || pos.y >= this->getNumCols()) {
			cout << "BAD GET DISPLAY" << endl;
			return '-';
	}

	return this->theDisplay[pos.x][pos.y];
}

vector<vector<char>> & Display::getDisplayArray() {
	return this->theDisplay;
}

int Display::getNumRows() {
	return this->numRows;
}

int Display::getNumCols() {
	return this->numCols;
}

void Display::setNumRows(int n) {
	this->numRows = n;
}

void Display::setNumCols(int n) {
	this->numCols = n;
}
