#include "player.h"
#include <cmath>

player::player(GLdouble _x,GLdouble _y,GLdouble _z,GLdouble _speed,GLdouble _step):
	y(_y),speed(_speed),step(_step)
{
	x = _x;
	z = _z;
	direction = 0.0;
}

void player::turnLeft()
{
	direction += step;
	if(direction > 2.0 * PI)
	{
		direction -= 2.0 * PI;
	}
}

void player::turnRight()
{
	direction -= step;
	if(direction < 0)
	{
		direction += 2.0 * PI;
	}
}

void player::forward()
{
	x += speed * cos(direction);
	z += speed * sin(direction);
}

void player::backward()
{
	x -= speed * cos(direction);
	z -= speed * sin(direction);
}

coord player::getCoord()
{
	return coord(x,y,z);
}

GLdouble player::getDir()
{
	return direction;
}

GLdouble player::getSpeed()
{
	return speed;
}