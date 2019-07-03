all: 
	g++ sim.cc --std=c++17 && ./a.out

clean:
	rm a.out