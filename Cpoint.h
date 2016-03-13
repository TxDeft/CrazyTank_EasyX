//Cpoint.h
#ifndef _CPOINT_H_
#define _CPOINT_H_
//include 和 前向引用声明.......................................................................
#include "common.h"



//..............................................................................................

class Cpoint
{
public:
	double x,y;//定义点的x/y坐标
	Cpoint(double x1=0.0,double y1=0.0);
    void  reset(double x1,double y1);//初始化点的位置函数
	double dist(Cpoint p1,Cpoint p2);
};
#endif
