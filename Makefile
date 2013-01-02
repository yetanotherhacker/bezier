all: bezier map1f subdivide

bezier: bezier.c bezier.h
	cc bezier.c -o bezier -lGL -lglut -lGLU

map1f: map.c
	cc map.c -o map1f -lGL -lglut -lGLU

subdivide: subdivide.c bezier.h
	cc subdivide.c -o subdivide -lGL -lglut -lGLU

