screen.x:  screen.o getChar.o cell.o freePool.o grid.o worm.o
	g++ -ggdb -o screen.x screen.o getChar.o cell.o freePool.o grid.o worm.o -lcurses -ltermcap

screen.o: screen.cpp
	g++ -c -ggdb screen.cpp -o screen.o

getChar.o: getChar.cpp 
	gcc -c -ggdb getChar.cpp -o getChar.o




test.x: cell.o freePool.o grid.o worm.o test.cpp
	g++ -ggdb -o test.x cell.o freePool.o grid.o worm.o test.cpp

cell.o: cell.hpp cell.cpp
	g++ -ggdb -c -o cell.o cell.cpp

freePool.o: freePool.hpp freePool.cpp
	g++ -ggdb -c -o freePool.o freePool.cpp

grid.o: grid.hpp grid.cpp	
	g++ -ggdb -c -o grid.o grid.cpp

worm.o: worm.hpp worm.cpp
	g++ -ggdb -c -o worm.o worm.cpp


clean:
	rm -f *.o *.x


cleanScreen:
	/bin/rm -f screen.x screen.o getChar.o *~
