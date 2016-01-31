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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_LINE_SMOOTH_HINT);
	glClearColor(0,0,0,0);
	
	GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat mat_specular[] = {0.7, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {100.0};
    GLfloat mat_position[] = {10, 10, 10, 1};
    
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
	if(c == 'w' || c == 'W') controler->doForward(pl);
	if(c == 'a' || c == 'A') pl->turnLeft();
	if(c == 'd' || c == 'D') pl->turnRight();
	if(c == 's' || c == 'S') controler->doBackward(pl);
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	coord cur = pl->getCoord();
	gluLookAt(cur.x,cur.y,cur.z,cur.x + cos(pl->getDir()),cur.y,cur.z + sin(pl->getDir()),0,1,0);
	controler->draw();
	glViewport(0,0,WIDTH,HEIGHT);
	/*
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0,10,0,0,0,0,cos(pl->getDir()),0,sin(pl->getDir()));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10,10,-10,10,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	*/
	//glViewport(500,0,500,500);
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
	pl = new player(0.5,0.5,0.5,0.1,0.1);
	controler = new gameMap("data.maz");
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(2*WIDTH,HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("3D Maze Game");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}