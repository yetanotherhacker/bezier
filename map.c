#include <stdio.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#define WIDTH 640
#define HEIGHT 480

GLfloat points[4][3];

void bezier()
{
      	glMapGrid1f(50, 0.0, 1.0);
      	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, points[0]);
	glEvalMesh1(GL_LINE, 0, 50);
	//make 50 sample points and draw
	//EvalMesh1 gives a lot cleaner code than looping through
	//glEvalCoord1f
	glFlush();
}

static void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	bezier();
	glFlush();
}

int main(int argc, const char *argv[])
{
	points[0][0] = 0.9;
	points[0][1] = 0.4;
	points[0][2] = 0;
	points[1][0] = 0.4;
	points[1][1] = 0.5;
	points[1][2] = 0;
	points[2][0] = -0.4;
	points[2][1] = -0.8;
	points[2][2] = 0;
	points[3][0] = -0.8;
	points[3][1] = -0.9;
	points[3][2] = 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
   	glutInitWindowSize(WIDTH, HEIGHT);
   	glutCreateWindow("The Fourth Holy Grail War");
   	glutDisplayFunc(display);
   	glClearColor(0.0,0.0,0.0,0.0);
   	glColor3f(1.0, 0.0, 0.0);
   	glEnable(GL_MAP1_VERTEX_3);
   	glutMainLoop();
}
