//Cpoint.h
#ifndef _CPOINT_H_
#define _CPOINT_H_
//include �� ǰ����������.......................................................................
#include "common.h"



//..............................................................................................

class Cpoint
{
public:
	double x,y;//������x/y����
	Cpoint(double x1=0.0,double y1=0.0);
    void  reset(double x1,double y1);//��ʼ�����λ�ú���
	double dist(Cpoint p1,Cpoint p2);
};
#endif
