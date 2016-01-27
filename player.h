#ifndef PLAYER_H
#define PLAYER_H
#include "headers.h"

class player
{
	GLdouble x;
	GLdouble z;
	const GLdouble y;//���ڹ̶���yˮƽ����
	const GLdouble speed;//�ƶ��ٶ�
	GLdouble direction;//Ŀǰ�ķ�����z�Ḻ��Ϊ0����ʱ�����ӣ�0��2pi
	const GLdouble step;//ת��Ĳ���
public:
	player(GLdouble _y,GLdouble _speed,GLdouble _step);
	void turnLeft();//��ת
	void turnRight();//��ת
	void forward();//ǰ��
	void backward();//����
	coord getCoord();//��ȡ��ǰ����
};

#endif