STD=c++17
MAINFILE=sim.cc
PYTHONLIB=-I/usr/include/python2.7 -lpython2.7

all: 
	g++ $(MAINFILE) --std=$(STD) $(PYTHONLIB) -Wall -pedantic

final: 
	g++ $(MAINFILE) --std=$(STD) $(PYTHONLIB) -O3 -w

run: final
	./a.out

clean:
	rm a.out