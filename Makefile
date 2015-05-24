all:
	g++ -O2 -Wall -o Airclick Airclick.cpp `pkg-config --cflags --libs opencv`
clean:
	rm -rf Airclick
