#include "player.h"
#include "gamemap.h"
player* pl;
gameMap* controler;
void init()
{
	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char c,int x,int y)
{
	if(c == 27) exit(0);
	if(c == 'e' || c == 'E') controler->doForward(pl);
}

void display()
{
	controler->draw();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GL_DOUBLE | GL_DEPTH | GL_RGBA);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("3D Maze Game");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}