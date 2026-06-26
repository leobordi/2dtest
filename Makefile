all: 2dtest

2dtest: 2dtest.c
	gcc 2dtest.c -O2 -Wall $(shell sdl2-config --cflags --libs) -lm -o ./build/2dtest

clean:
	rm -f 2dtest
