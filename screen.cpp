/* 
 * Chad Vink
 * Project 5
 * screen.cpp
 * Main file to run the game
 */

#include <curses.h>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "getChar.hpp"
#include "grid.hpp"
#include "freePool.hpp"
#include "worm.hpp"

void startup( void );
void terminate( int score, char dir );
bool limitDirection( char dir, char prevDar );
char getDirection( Grid *grid, int currentRow, int currentCol, int prevDir);
char optimalHorzDirection( Grid *grid, int currentRow, int currentCol );
char optimalVertDirection( Grid *grid, int currentRow, int currentCol );

int main(int argc, char* argv[2])
{
	if( argc < 2 ){
		cout << "Enter Height(9-25) and Width(9-80) of game.\n";
		exit(1);
	}

	srand(time(NULL));
	int height = atoi( argv[1] );
	int width = atoi( argv[2] );
	int currentRow = height/2;
	int currentCol = width/2;
	int score = 0;
	int wormSize = 1;
	stringstream stream;
	string munchieString;
	string scoreString;
	char dir;
	char prevDir;
	
	if( height < 9 || height > 25 || width < 9 || width > 80 )
		exit(1);
	startup();
	curs_set(0);

	Grid *grid = new Grid( height, width );
	Worm worm = Worm( grid->getFreePool().size() );

	mvaddstr(height, 0, "Worm");
	mvaddstr(height, width-9, "Score: ");
	
	int i = 0;
	while( i < height ){
		mvaddch( i, 0, '*' );
		mvaddch( i, width-1, '*' );
		i += 1;
	}
	i = 0;
	while( i < width ){
		mvaddch( 0, i, '*' );
		mvaddch( height-1, i, '*' );
		i+=1;
	}
	
	worm.insert( currentRow, currentCol );
	grid->remove( currentRow, currentCol );
	mvaddch( currentRow, currentCol, '@' );

	score = wormSize - 1;
	stream << score;
	scoreString = stream.str();
	mvaddstr( height, width, scoreString.c_str() );
	stream.str(string());

	int munchieValue = ( rand() % 9 ) + 1;
	grid->makeMunchie();
	stream << munchieValue;
	munchieString = stream.str();
	mvaddstr( grid->getMunchie().getRow(), grid->getMunchie().getColumn(), munchieString.c_str() );
	stream.str(string());
	
	refresh();
	prevDir = ' ';
	while( true ){

		dir = getDirection( grid, currentRow, currentCol, prevDir);

		//if ( limitDirection( dir, prevDir ) ) 
		//	dir = prevDir;

		if( wormSize - 1 != 0 )
			mvaddch( currentRow, currentCol, 'o' );

		if( dir == 'w' )
			--currentRow;
		else if( dir == 's' )
			++currentRow;
		else if( dir == 'a' )
			--currentCol;
		else if( dir == 'd' )
			++currentCol;

		if ( dir != ' ' && grid->isWall( currentRow, currentCol ) ){
			terminate(score, dir);
		}
		score = wormSize - 1;
		stream << score;
		scoreString = stream.str();
		mvaddstr( height, width, scoreString.c_str() );
		stream.str(string());

	
		if( grid->isMunchie( currentRow, currentCol ) ){
			wormSize += munchieValue;
			munchieValue = ( rand() % 9 ) + 1;
			grid->makeMunchie();
			stream << munchieValue;
			munchieString = stream.str();
			mvaddstr( grid->getMunchie().getRow(), grid->getMunchie().getColumn(), munchieString.c_str() );
			stream.str(string());
		}
		
		if( worm.getLength() > wormSize ){
			worm.remove();
			grid->insert( worm.getWorm(worm.getTail()).getRow(), worm.getWorm(worm.getTail()).getColumn() );
			mvaddch( worm.getWorm(worm.getTail()).getRow(), worm.getWorm(worm.getTail()).getColumn(), ' ' );
		}
		worm.insert( currentRow, currentCol );
		grid->remove( currentRow, currentCol );
		if( dir == 'w' )
			mvaddch( currentRow, currentCol, '^' );
		else if( dir == 's' )
			mvaddch( currentRow, currentCol, 'V' );
		else if( dir == 'a' )
			mvaddch( currentRow, currentCol, '<' );
		else if( dir == 'd' )
			mvaddch( currentRow, currentCol, '>' );
		
		prevDir = dir;
		refresh();
	}
	
}

char getDirection( Grid *grid, int currentRow, int currentCol, int prevDir )
{
     	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 40000;
	select(0,NULL,NULL,NULL,&tv);


// going up
	if ( grid->getMunchie().getRow() < currentRow ){
		if ( prevDir == 's' ){
			if ( grid->isWall( currentRow, currentCol+1 ) || grid->isWall( currentRow, currentCol-1 ) )
				return 's';
			return optimalHorzDirection( grid, currentRow, currentCol );
		}
			
		if ( grid->isWall( currentRow-1, currentCol ) )
			return optimalHorzDirection( grid, currentRow, currentCol );
		else
			return 'w';
	}

	if ( grid->getMunchie().getRow() > currentRow){
		if ( prevDir == 'w' ){
			if ( grid->isWall( currentRow, currentCol+1 ) || grid->isWall( currentRow, currentCol-1 ) )
				return 'w';
			return optimalHorzDirection( grid, currentRow, currentCol );
		}

		if ( grid->isWall( currentRow+1, currentCol ) )
			return optimalHorzDirection( grid, currentRow, currentCol );
		else
			return 's';
	}	

	if ( grid->getMunchie().getColumn() > currentCol){
		if ( prevDir == 'a' ){
			if ( grid->isWall( currentRow+1, currentCol ) || grid->isWall( currentRow-1, currentCol ) )
				return 'a';
			return optimalVertDirection( grid, currentRow, currentCol );
		}

		if ( grid->isWall( currentRow, currentCol+1 ) )
			return optimalVertDirection( grid, currentRow, currentCol );
		else
			return 'd';
	}

	if ( grid->getMunchie().getColumn() < currentCol){
		if ( prevDir == 'd' ){
			if ( grid->isWall( currentRow+1, currentCol ) || grid->isWall( currentRow-1, currentCol ) )
				return 'd';
			return optimalVertDirection( grid, currentRow, currentCol );
		}

		if (grid->isWall( currentRow, currentCol-1 ))
			return optimalVertDirection( grid, currentRow, currentCol );
		else
			return 'a';
	}
	return prevDir;
}


void startup( void )
{
	initscr();
	clear();
	noecho();
	cbreak();
}	

void terminate( int score, char dir)
{
	mvcur( 0, COLS - 1, LINES - 1, 0 );
	clear();
	refresh();
	endwin();
	cout << " You lost with a score of: " << score << endl;
	cout << "This Direction: " << dir << endl;
	exit(1);
}

bool limitDirection( char dir, char prevDir )
{
	
		if( dir == 'w' && prevDir == 's')
			return true;
		else if( dir == 's' && prevDir == 'w' )
			return true;
		else if( dir == 'a' && prevDir == 'd' )
			return true;
		else if( dir == 'd' && prevDir == 'a' )
			return true;
		return false;
}

char optimalVertDirection( Grid *grid, int currentRow, int currentCol )
{
	int up = 0;
	int down = 0;
	int row = currentRow;
	int col = currentCol;

	while( !grid->isWall( row-1, col ) ){
		up++;
		row++;
	}
	while( !grid->isWall( row+1, col ) ){
		down++;
		row--;
	}

	return up > down ? 'w' : 's';
}


char optimalHorzDirection( Grid *grid, int currentRow, int currentCol )
{
	int left = 0;
	int right = 0;
	int row = currentRow;
	int col = currentCol;

	while( !grid->isWall( row, col-1 ) ){
		left++;
		col--;
	}
	while( !grid->isWall( row, col+1 ) ){
		right++;
		col++;
	}

	return left > right ? 'a' : 'd';

}

