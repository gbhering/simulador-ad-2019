all: 
	g++ sim.cc --std=c++17 -Wall -pedantic && ./a.out

final: 
	g++ sim.cc --std=c++17 -O3 -Wall -pedantic -Werror && ./a.out

clean:
	rm a.out