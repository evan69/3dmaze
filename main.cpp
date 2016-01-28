#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include "player.h"
#include "gamemap.h"
player* pl;
gameMap* controler;

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

void init()
{
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,WIDTH,HEIGHT);
	
	GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {100.0};
    GLfloat mat_position[] = {0, 0, 50, 1};
    
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    
    glLightfv(GL_LIGHT0, GL_POSITION, mat_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, mat_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, mat_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
}

void keyboard(unsigned char c,int x,int y)
{
	if(c == 27) exit(0);
	if(c == 'e' || c == 'E') controler->doForward(pl);
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	coord cur = pl->getCoord();
	gluLookAt(cur.x,cur.y,cur.z,0,0,0,-cur.z,0,cur.x);
	controler->draw();
	glColor3d(1,0,0);
	//drawCube(1,1,1);
	//glutSolidCube(1);
	glFlush();
	glutSwapBuffers();
}

void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,1,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc,char** argv)
{
	pl = new player(0.2,0.5,0.2,1,1);
	controler = new gameMap("data.maz");
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("3D Maze Game");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}