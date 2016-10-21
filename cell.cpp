/* 
 * Chad Vink
 * Project 5
 * cell.cpp
 * This is the implemention file for the Cell class.
 */

#include "cell.hpp"

Cell::Cell(int row, int col)
{
	_row = row;
	_col = col;
}

int Cell::getRow()
{
	return _row;
}

void Cell::setRow(int row)
{
	_row = row;
}

int Cell::getColumn()
{
	return _col;
}

void Cell::setColumn(int col)
{
	_col = col;
}
