#include <stdio.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include "bezier.h"

int lvl = 0; //subdivision level

void display()
{
	int i;
	float pixels[HEIGHT*WIDTH*3];
	screen = pixels;
	for(i= 0; sizeof(pixels)>i; ++i) {
		pixels[i] = 0.1;
	}
	line(100,100,500,200,RED);

	//subdivide and draw when appropriate
	if(lvl==0)
		bz2(bx,by2,GREEN);
	float salx[4], saly[4], sarx[4], sary[4];
	subdivide(bx,by2,0.5,salx,saly,sarx,sary);

	if(lvl==1) {
		bz2(salx,saly,BLUE);
		bz2(sarx,sary,ORCHID);
	}

	float sblx[4], sbly[4], sbrx[4], sbry[4];
	float sclx[4], scly[4], scrx[4], scry[4];
	subdivide(salx,saly,0.5,sblx,sbly,sbrx,sbry);
	subdivide(sarx,sary,0.5,sclx,scly,scrx,scry);

	if(lvl==2) {
		bz2(sblx,sbly,BLUE);
		bz2(sbrx,sbry,ORCHID);
		bz2(sclx,scly,RED);
		bz2(scrx,scry,GREEN);
	}

	float sdlx[4], sdly[4], sdrx[4], sdry[4];
	float selx[4], sely[4], serx[4], sery[4];
	float sflx[4], sfly[4], sfrx[4], sfry[4];
	float sglx[4], sgly[4], sgrx[4], sgry[4];
	subdivide(sblx,sbly,0.5,sdlx,sdly,sdrx,sdry);
	subdivide(sbrx,sbry,0.5,selx,sely,serx,sery);
	subdivide(sclx,scly,0.5,sflx,sfly,sfrx,sfry);
	subdivide(scrx,scry,0.5,sglx,sgly,sgrx,sgry);

	if(lvl==3) {
		bz2(sdlx,sdly,BLUE);
		bz2(sdrx,sdry,ORCHID);
		bz2(selx,sely,RED);
		bz2(serx,sery,GREEN);
		bz2(sflx,sfly,BLUE);
		bz2(sfrx,sfry,ORCHID);
		bz2(sglx,sgly,RED);
		bz2(sgrx,sgry,GREEN);
	}


	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_FLOAT,pixels);
	glutSwapBuffers();
}

main(int argc, char *argv[])
{
	if(argc==2)
		lvl = argv[1][0] - '0'; //find subdivision level requested
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutCreateWindow("Twelve Command Seals");
	glutDisplayFunc(display);
	glutMainLoop();
}
