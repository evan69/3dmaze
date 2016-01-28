#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

const GLdouble PI = 3.1415926535;

const int WIDTH = 500;
const int HEIGHT = 500;

void drawCube(GLdouble x,GLdouble y,GLdouble z)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glScaled(x,y,z);
	glutSolidCube(1);
	glPopMatrix();
}

struct coord
{
	GLdouble x,y,z;
	coord(GLdouble _x = 0,GLdouble _y = 0,GLdouble _z = 0)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};