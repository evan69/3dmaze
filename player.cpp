#include "player.h"
#include <cmath>

player::player(GLdouble _y,GLdouble _speed,GLdouble _step):
	y(_y),speed(_speed),step(_step)
{
	x = z = 0.0;
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