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

char time[] = "00:00:00";
char win[] = "You have won!Press Esc to quit.";
int second = 0;
int startTime,curTime;
int winFlag = 0;

void drawFlag()
{   
	glColor3d(1,0,0);
	glRasterPos3f(-0.1,0,0);
	for (int i = 0;i < 5;++i)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, time[i]);
	if(winFlag == 1)
	{
		glRasterPos3f(-0.7,-0.5,0);
		for (int i = 0;i < 32;++i)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, win[i]);
	}
}

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
    GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat mat_specular[] = {0.7, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {100.0};
    GLfloat mat_position[] = {3, 3, 3, 1};
    
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
	if(winFlag == 1) return;
	if(c == 'w' || c == 'W') controler->doForward(pl);
	if(c == 'a' || c == 'A') pl->turnLeft();
	if(c == 'd' || c == 'D') pl->turnRight();
	if(c == 's' || c == 'S') controler->doBackward(pl);
	controler->checkWin(pl,&winFlag);
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0,0,0.5,0.3);
	glViewport(0,0,WIDTH,HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	coord cur = pl->getCoord();
	gluLookAt(cur.x,cur.y,cur.z,cur.x + cos(pl->getDir()),cur.y,cur.z + sin(pl->getDir()),0,1,0);
	controler->draw();

	//glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(1,1,1,1);
	glViewport(0,HEIGHT,WIDTH,100);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	drawFlag();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	/*
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//gluLookAt(0,10,0,0,0,0,1,0,0);
	glTranslated(0,0,10);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-10,10,10,-10,0.1,100);
	//gluPerspective(90,1,0.1,100);
	
	glBegin( GL_POLYGON );
	glVertex2f( -0.5, -0.5 );
	glVertex2f( -0.5, 0.5 );
	glVertex2f( 0.5, 0.5 );
	glVertex2f( 0.5, -0.5 );
	glEnd();
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	*/
	//glFlush();
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

void idle()
{
	if(winFlag == 1) return;
	curTime = glutGet(GLUT_ELAPSED_TIME);
	second = (int)(curTime - startTime) / 1000;
	int minute = second / 60;
	time[0] = '0' + minute / 10;
	time[1] = '0' + minute % 10;
	time[3] = '0' + (second - minute * 60) / 10;
	time[4] = '0' + (second - minute * 60) % 10;
	glutPostRedisplay();
}

int main(int argc,char** argv)
{
	pl = new player(0.5,0.3,0.5,0.1,0.1);
	controler = new gameMap("data.maz");
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(WIDTH,HEIGHT+100);
	glutInitWindowPosition(100,100);
	glutCreateWindow("3D Maze Game");
	startTime = glutGet(GLUT_ELAPSED_TIME);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}