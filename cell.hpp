/*
 * Chad Vink
 * Project 5
 * cell.hpp
 * This is the header file for the Cell class.
 */

#ifndef _cell_hpp
#define _cell_hpp

using namespace std;

class Cell {
public:
	Cell() {_row = _col = -1;};
	Cell(int row, int col);
	~Cell() {}
	int getRow();
	void setRow(int row);
	int getColumn();
	void setColumn(int col);
	
private:
	int _row, _col;
};


#endif
