/*
 * Chad Vink
 * Project 5
 * grid.cpp
 * Implementaions for the Grid class that runs in conjection
 * with the FreePool class.
 */

#include "grid.hpp"

Grid::Grid( int height, int width )
{
	_pool = FreePool();
	_height = height;
	_width = width;
	_maxPool = height-2 * width-2;
	_endRow = height-1;
	_endCol = width-1;
	init();
}


Grid::~Grid()
{ 
	delete[] _grid;
	//delete _pool;
}


void Grid::init()
{
	_grid = new int*[_height];
	for( int i = 0; i < _height; ++i ){
		_grid[i] = new int[_width];
		for( int j = 0; j < _width; ++j ){
			if( j == 0 || j == _width-1 || i == 0 || i == _height-1 ){
				_grid[i][j] = -1;
			}
			else{
				_pool.insert( _grid[i][j], i, j );
			}
		}
	}
}

void Grid::insert( int row, int col )
{
	if( _pool.size() == _maxPool )
		return;
	
	_pool.insert( _grid[row][col], row, col);
	
	_endRow = _pool.getValues( _pool.size()-1 ).getRow();
	_endCol = _pool.getValues( _pool.size()-1 ).getColumn();
}

void Grid::remove( int row, int col )
{
	if( _pool.size() == 0 )
		return;


	_pool.remove( _grid[row][col] );
	_grid[_endRow][_endCol] = _grid[row][col];
	_grid[row][col] = -1;
	
	_endRow = _pool.getValues( _pool.size()-1 ).getRow();
	_endCol = _pool.getValues( _pool.size()-1 ).getColumn();
}

bool Grid::isMunchie( int row, int col )
{
	return _pool.isMunchie( row, col );
}

void Grid::makeMunchie()
{
	_pool.setMunchie( rand() % _pool.size() );
}

void Grid::print()
{
	for( int i = 0; i < _height; ++i ){
		for( int j = 0; j < _width; ++j ){
			if ( isMunchie( i, j ) )
				cout << left << setw(4) << "M";
			else
				cout << left << setw(4) << _grid[i][j];
			
		}
		cout << endl;
	}
}

bool Grid::isWall( int row, int col )
{
	if( _grid[row][col] == -1 )
		return true;
	return false;
}
