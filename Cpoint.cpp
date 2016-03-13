//Cpoint.cpp
//include 和 前向引用声明.......................................................................
#include "common.h"
#include"Cpoint.h"
using namespace std;

//..............................................................................................

Cpoint::Cpoint(double x1/*=0.0*/,double y1/*=0.0*/)
{
	x=x1;
	y=y1;
}

void Cpoint::reset(double x1,double y1)
{
	x=x1;
	y=y1;
}


double Cpoint::dist(Cpoint p1,Cpoint p2)
{
	double dx=p1.x-p2.x;
	double dy=p1.y-p2.y;
	double dr=sqrt(dx*dx+dy*dy);
	return dr;
}
