subfiles = $(wildcard */*.c)

all: main.c $(subfiles)
	gcc -o gr_raytracer main.c $(subfiles) -g -lm
