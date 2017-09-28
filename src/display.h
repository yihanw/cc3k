#ifndef _DISPLAY_
#define _DISPLAY_

#include <vector>
struct Position;

class Display {
private:
	std::vector < std::vector <char> > theDisplay;
	int numRows = 0;
	int numCols = 0;

public:
	Display();
	~Display();
	void setDisplayRow(std::vector<char> row); // set the row of the display
	std::vector<std::vector<char>> & getDisplayArray(); 

	void setDisplayAtPos(Position pos, char rep); // set rep at position, pos, for display
	char getDisplayAtPos(Position pos); // get the display at the position, pos

	int getNumRows(); // get the number of the row
	int getNumCols(); // get the number of the column

	void setNumRows(int n); // set the number of row to n
	void setNumCols(int n); // set the number of column to n
};

#endif
