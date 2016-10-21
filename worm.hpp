/*
 * Chad Vink
 * Project 5
 * worm.hpp
 * Header class for the Worm class.
 */

#ifndef _worm_hpp
#define _worm_hpp

#include "cell.hpp"
#include <iostream>

using namespace std;

class Worm{
public:
	Worm( int size );
	~Worm() {}

	int getHead() { return _head; }
	int getTail() { return _tail; }
	int getLength() { return _length; }
	Cell getWorm( int index );
	
	void insert( int row, int col );
	void remove();
	void print();

private:
	Cell *_worm;
	int _head, _tail, _length, _maxLength;
};

#endif
