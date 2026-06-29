all: 2dtest

2dtest: 2dtest.c
	gcc -O2 2dtest.c `sdl2-config --cflags` `sdl2-config --libs` -lm -o 2dtest -Wall -W

clean:
	rm -f 2dtest
