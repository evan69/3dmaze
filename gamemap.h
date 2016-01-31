#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "headers.h"
#include "player.h"
#include <vector>
using std::vector;

extern const GLdouble PI;
extern const int WIDTH;
extern const int HEIGHT;
extern void drawCube(GLdouble x,GLdouble y,GLdouble z);

struct wall
{
	int x;
	int z;
	enum wallDir{WALL_X,WALL_Z};
	enum wallDir dir;
	wall(int _x,int _z,wallDir _dir)
	{
		x = _x;
		z = _z;
		dir = _dir;
	}
	void draw();
};

class gameMap
{
	vector<wall> data;
	void readin(char*);
	coord target;
public:
	gameMap(char* file);
	bool doForward(player*);
	bool doBackward(player*);
	void draw();
	void drawFlag();
};

#endif