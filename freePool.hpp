/*
 * Chad Vink
 * Project 5
 * freePool.hpp
 * Header file for the FreePool class that runs 
 * in conjunction with the Grid class.
 */

#ifndef _freePool_hpp
#define _freePool_hpp

using namespace std;
#include "cell.hpp"
#include <vector>
#include <iostream>

class FreePool {
public:
	FreePool();
	~FreePool() {}

	void insert( int &index, int row, int col );
	void remove( int index );
	int size();
	void print();
	
	Cell getValues( int index );
	bool isMunchie( int row, int col );
	void setMunchie( int index );
	Cell getMunchie() { return _munchie; }

private:
	vector<Cell> _freePool;
	int _lastIndex;
	Cell _munchie;

};

#endif
