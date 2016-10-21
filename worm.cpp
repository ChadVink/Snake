/*
 * Chad Vink
 * Project 5
 * worm.cpp
 * Implementation file for the Worm class.
 */

#include "worm.hpp"

Worm::Worm( int size )
{
	_maxLength = size;
	_length = _tail = _head = 0;
	_worm = new Cell[size];
}

void Worm::insert( int row, int col )
{
	_worm[_head] = Cell( row, col );
	_head += 1;
	_length += 1;
	if( _head == _maxLength )
		_head = 0;
}

void Worm::remove()
{
	_tail += 1;
	_length -= 1;
	if( _tail == _maxLength )
		_tail = 0;
}


void Worm::print()
{
	cout << "Worm: ";
	for( int i = _tail; i < _head; ++i ){
		cout << _worm[i].getRow() << "," << _worm[i].getColumn() << " -> ";
	}
	cout << endl;
}

Cell Worm::getWorm( int index )
{
	return _worm[index];
}
