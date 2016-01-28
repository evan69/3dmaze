#ifndef PLAYER_H
#define PLAYER_H
#include "headers.h"

extern const GLdouble PI;
extern const int WIDTH;
extern const int HEIGHT;
extern void drawCube(GLdouble x,GLdouble y,GLdouble z);

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

class player
{
	GLdouble x;
	GLdouble z;
	const GLdouble y;//处于固定的y水平面上
	const GLdouble speed;//移动速度
	GLdouble direction;//目前的方向，以z轴负向为0，逆时针增加，0到2pi
	const GLdouble step;//转向的步长
public:
	player(GLdouble _x,GLdouble _y,GLdouble _z,GLdouble _speed,GLdouble _step);
	void turnLeft();//左转
	void turnRight();//右转
	void forward();//前进
	void backward();//后退
	coord getCoord();//获取当前坐标
	GLdouble getDir();//
	GLdouble getSpeed();
};

#endif