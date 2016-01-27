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
}

void player::forward()
{
	x -= speed * sin(direction);
	z -= speed * cos(direction);
}

void player::backward()
{
	x += speed * sin(direction);
	z += speed * cos(direction);
}

coord player::getCoord()
{
	return coord(x,y,z);
}