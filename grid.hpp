/*
 * Chad Vink
 * Project 5
 * Grid.hpp
 * Header file for the Grid class that runs in conjunction
 * with the FreePool class.
 */

#ifndef _grid_hpp
#define _grid_hpp

#include "freePool.hpp"
#include "cell.hpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>


using namespace std;

class Grid{
public:
	Grid( int height, int width );
	~Grid();

	FreePool getFreePool() { return _pool; }
	bool isWall( int row, int col );
	bool isMunchie( int row, int col );
	void makeMunchie();
	Cell getMunchie() { return _pool.getMunchie(); }
	void insert( int row, int col );
	void remove( int row, int col );
	
	void print();

private:
	int **_grid;
	FreePool _pool;

	int _maxPool, _height, _width;
	int _endRow, _endCol;
	
	void init();
};

#endif
