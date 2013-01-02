#include <stdio.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include "bezier.h"


void display()
{
	int i;
	float pixels[HEIGHT*WIDTH*3];
	screen = pixels;
	for(i= 0; sizeof(pixels)>i; ++i) {
		pixels[i] = 0.1;
	}
	line(100,100,500,200,RED);
	bz2(bx,by3,GREEN);
	bz2(bx,by,BLUE);
	bz2(bx,by1,RED);
	bz2(bx,by2,ORCHID);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_FLOAT,pixels);
	glutSwapBuffers();
}

main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("Eight Black Keys");
	glutDisplayFunc(display);
	glutMainLoop();
}
