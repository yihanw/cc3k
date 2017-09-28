#ifndef _POS_
#define _POS_
#include <math.h>

//Position in 2D space
struct Position {
	int x;
	int y;

private:
	int abs(int x) {
		if (x <= 0) {
			return -x;
		}
		else {
			return x;
		}
	}

public:

	Position() : x{ 0 }, y{ 0 } {}

	Position(int myx, int myy) : x{ myx }, y{ myy } {}

	Position & operator= (const Position & other) {
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

      bool operator== (Position & pos) {
		return (x == pos.x && y == pos.y);
	}

	bool isInRadiusOf(Position pos) {
		return abs(pos.x - this->x) <= 1 && abs(pos.y - this->y) <= 1;
	}
};

#endif
