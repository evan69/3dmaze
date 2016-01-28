#include "gamemap.h"
#include <iostream>
#include <fstream>
#include <cmath>
using std::ifstream;
using std::cout;
using std::endl;

void wall::draw()
{
	glColor3d(0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslated(x,0,z);
	if(dir == wall::WALL_X)
	{
		glTranslated(0.5,0,0);
		drawCube(1,1,0.1);
	}
	if(dir == wall::WALL_Z)
	{
		glTranslated(0,0,0.5);
		drawCube(0.1,1,1);
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
	int tmp_x,tmp_z;
	char type;
	while(1)
	{
		fin >> tmp_x >> tmp_z;
		target = coord(tmp_x,0,tmp_z);
		fin >> type;
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
	for(vector<wall>::iterator it = data.begin;it != data.end;++it)
	{
		if(it->dir == wall::WALL_X)
		{
			/*if((pl->getCoord().z - it->z) * (pl->getCoord().z + pl->getSpeed() * sin(pl->getDir())) < 0.0
				&& (pl->getCoord().x + (it->z - pl->getCoord().z) / tan(pl->getDir()) - it->x) * 
				(pl->getCoord().x + (it->z - pl->getCoord().z) / tan(pl->getDir()) - it->x - 1) < 0.0)
			*/
			//if(pl->getCoord().x > it->x && pl->getCoord().x < it->x + 1 && pl->getCoord().z > )
			if(abs(pl->getCoord().x - it->x - 0.5) < 0.5 && abs(pl->getCoord().z - it->z) < 0.1)
			{
				if(pl->getCoord().z < it->z && pl->getDir() < PI) return false;
				if(pl->getCoord().z > it->z && pl->getDir() > PI) return false;
			}
		}
		if(it->dir == wall::WALL_Z)
		{
			if(abs(pl->getCoord().z - it->z - 0.5) < 0.5 && abs(pl->getCoord().x - it->x) < 0.1)
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

}

void gameMap::draw()
{
	for(vector<wall>::iterator it = data.begin();it != data.end();++it)
	{
		it->draw();
	}
}
