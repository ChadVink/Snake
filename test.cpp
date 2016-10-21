#include <iostream>
#include <cstdlib>
#include "cell.hpp"
#include "freePool.hpp"
#include "grid.hpp"
#include "worm.hpp"

using namespace std;

int main(int argc, char* argv[2])
{
	int height = atoi( argv[1] );
	int width = atoi( argv[2] );

	Grid grid = Grid( height, width );
	grid.makeMunchie();
	grid.print();
	cout << endl;

	Worm worm = Worm( grid.getFreePool().size() - 1 );

	worm.insert( 1, 2 );
	grid.remove( 1, 2 );
	worm.insert( 2, 2 );
	grid.remove( 2, 2 );
	worm.insert( 3, 2 );
	grid.remove( 3, 2 );
	
	grid.print();
	cout << endl;	

	for( int i = 4; i < height - 2; ++i ){
		worm.insert(i, 2);
		grid.remove(i, 2);

		grid.insert(i-worm.getLength()+1, 2);
		worm.remove();
		grid.print();
		cout << endl;
	}

	//grid.getFreePool().print();
/*
	Worm *worm = new Worm( max, height, width );
	worm->wormInsert( 1,2 );
	worm->wormInsert( 2,2 );
	worm->wormInsert( 3,2 );
	worm->getGrid()->print();
	worm->print();
	cout << endl;

	for( int i = 4; i <= height; ++i ){
		worm->wormInsert( i,2 );
		
		worm->wormRemove();
		worm->getGrid()->print();
		worm->print();
		cout << endl;
	}

	grid->gridRemove( 5,5 );
	grid->print();
	cout << endl;
	
	grid->gridInsert( 4,3 );
	grid->print();
	cout << endl;
	
	grid->getFreePool()->print();
*/
	
	return 0;
}

