/*
 * Chad Vink
 * Project 5
 * freePool.cpp
 * This is the implention file for the FreePool class that
 * run in conjunction with the Grid class.
 */

#include "freePool.hpp"

FreePool::FreePool() 
{ 
	_lastIndex = 0;
	_munchie = Cell();
}

void FreePool::insert( int &index, int row, int col )
{
	index = _lastIndex-1;
	Cell cell = Cell( row, col );
	_freePool.push_back( cell );
	_lastIndex += 1;
}

void FreePool::remove( int index )
{
	_freePool[index] = _freePool[_lastIndex-1];
	_freePool.pop_back();
	_lastIndex -= 1;
}

int FreePool::size()
{
	return _lastIndex;
}

void FreePool::print()
{
	for( int i = 0; i < _lastIndex; ++i ) {
		cout << "At index: " << i << endl;
		cout << "Row: " << _freePool[i].getRow() << endl;
		cout << "Column: " << _freePool[i].getColumn() << endl;
		cout << endl;
	}
}

Cell FreePool::getValues( int index )
{
	return _freePool[index];
}

bool FreePool::isMunchie( int row, int col )
{
	if( _munchie.getRow() == row && _munchie.getColumn() == col )
		return true;
	return false;
}

void FreePool::setMunchie( int index )
{
	_munchie = Cell( _freePool[index].getRow(), _freePool[index].getColumn() );
}

