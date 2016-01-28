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
	const GLdouble y;//���ڹ̶���yˮƽ����
	const GLdouble speed;//�ƶ��ٶ�
	GLdouble direction;//Ŀǰ�ķ�����z�Ḻ��Ϊ0����ʱ�����ӣ�0��2pi
	const GLdouble step;//ת��Ĳ���
public:
	player(GLdouble _x,GLdouble _y,GLdouble _z,GLdouble _speed,GLdouble _step);
	void turnLeft();//��ת
	void turnRight();//��ת
	void forward();//ǰ��
	void backward();//����
	coord getCoord();//��ȡ��ǰ����
	GLdouble getDir();//
	GLdouble getSpeed();
};

#endif