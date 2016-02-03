#include "gamemap.h"
#include <iostream>
#include <fstream>
#include <cmath>
using std::ifstream;
using std::cout;
using std::endl;

void wall::draw()
{
	glColor3d(0,0.5,0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	if(dir == wall::WALL_X)
	{
		glTranslated(x + 0.5,0.5,z);
		drawCube(1.1,1,0.1);
	}
	if(dir == wall::WALL_Z)
	{
		glTranslated(x,0.5,z + 0.5);
		drawCube(0.1,1,1.1);
	}
	glPopMatrix();
}

gameMap::gameMap(char* file)
{
	readin(file);
}

void gameMap::readin(char* file)
{
	ifstream fin(file);
	if(!fin.is_open())
	{
		cout << "can not open\n";
		exit(-1);
	}
	int tmp_x,tmp_z;
	char type;
	fin >> tmp_x >> tmp_z;
	cout << tmp_x << tmp_z << endl;
	target = coord(tmp_x,0,tmp_z);
	while(1)
	{
		fin >> type;
		cout << type << endl;
		if(type == 'e') break;
		fin >> tmp_x >> tmp_z;
		if(type == 'x') data.push_back(wall(tmp_x,tmp_z,wall::WALL_X));
		else if(type == 'z') data.push_back(wall(tmp_x,tmp_z,wall::WALL_Z));
		else
		{
			cout << "Error occurs when reading data file,please make sure its legality!";
			exit(-1);
		}
		
	}
	fin.close();
}

bool gameMap::doForward(player* pl)
{
	for(vector<wall>::iterator it = data.begin();it != data.end();++it)
	{
		if(it->dir == wall::WALL_X)
		{
			if(abs(pl->getCoord().x - it->x - 0.5) < 0.55 && abs(pl->getCoord().z - it->z) < 0.15)
			{
				if(pl->getCoord().z < it->z && pl->getDir() < PI) return false;
				if(pl->getCoord().z > it->z && pl->getDir() > PI) return false;
			}
		}
		if(it->dir == wall::WALL_Z)
		{
			if(abs(pl->getCoord().z - it->z - 0.5) < 0.55 && abs(pl->getCoord().x - it->x) < 0.15)
			{
				if(pl->getCoord().x < it->x && (pl->getDir() < PI / 2 || pl->getDir() > 3 * PI / 2)) return false;
				if(pl->getCoord().x > it->x && (pl->getDir() > PI / 2 && pl->getDir() < 3 * PI / 2)) return false;
			}
		}
	}
	pl->forward();
	return true;
}

bool gameMap::doBackward(player* pl)
{
	for(vector<wall>::iterator it = data.begin();it != data.end();++it)
	{
		if(it->dir == wall::WALL_X)
		{
			if(abs(pl->getCoord().x - it->x - 0.5) < 0.5 && abs(pl->getCoord().z - it->z) < 0.2)
			{
				if(pl->getCoord().z < it->z && pl->getDir() > 3 * PI / 2) return false;
				if(pl->getCoord().z > it->z && pl->getDir() < PI / 2) return false;
			}
		}
		if(it->dir == wall::WALL_Z)
		{
			if(abs(pl->getCoord().z - it->z - 0.5) < 0.5 && abs(pl->getCoord().x - it->x) < 0.2)
			{
				if(pl->getCoord().x < it->x && (pl->getDir() > PI / 2 && pl->getDir() < 3 * PI / 2)) return false;
				
				if(pl->getCoord().x > it->x && (pl->getDir() < PI / 2 || pl->getDir() > 3 * PI / 2)) return false;
				
			}
		}
	}
	pl->backward();
	return true;
}

void gameMap::draw()
{
	for(vector<wall>::iterator it = data.begin();it != data.end();++it)
	{
		it->draw();
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3d(0.1,0.1,0.1);
	drawCube(20,0.1,20);
	glPopMatrix();
	drawFlag();
}

void gameMap::drawFlag()
{
	glRasterPos3f(target.x+0.5,0.5,target.z+0.5);
	glColor3d(1,0,0);
	char t[] = "here";
	/*
	for(unsigned int i = 0;i < 4;i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, t[i]);
	*/
	glPushMatrix();
	glTranslated(target.x+0.5,0.5,target.z+0.5);
	glutSolidSphere(0.1,30,30);
	glPopMatrix();
}

void gameMap::checkWin(player* pl,int* flag)
{
	coord pos = pl->getCoord();
	*flag = 0;
	if(pos.x > target.x && pos.x < target.x + 1)
		if(pos.z > target.z && pos.z < target.z + 1)
			*flag = 1;
}
