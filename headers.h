#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>

const GLdouble PI = 3.1415926535;

struct coord
{
	GLdouble x,y,z;
	coord(GLdouble _x,GLdouble _y,GLdouble _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};