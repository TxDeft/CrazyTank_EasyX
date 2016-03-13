//CbulletBase.h
#ifndef _CBULLETBASE_H_
#define _CBULLETBASE_H_

//include 和 前向引用声明.......................................................................
#include "common.h"



//..............................................................................................

class CbulletBase
{
public:
	CbulletBase();//子弹的构造函数
	void createBullet(CcombatData &combatData);
	void eliminateBullet();//清除 只改变exsit的值，其它都不要碰 
    int changePositionTo(double newx,double newy);
	bool judgeCollision(int x,int y,CcombatData & combatData);  //碰撞了返回true
	
	virtual void bomb(CcombatData &combatData,CcombatShower &combatShower);//子弹的爆炸数据包传来的数据
    virtual void fly(CcombatData &combatData,CcombatShower &combatShower);//子弹的移动函数 

	bool exist;//=0;//用于描述炮弹是否存在
	bool bombOrNot;//用于检测是否爆炸了
	Cpoint position;//子弹当前点的位置
	double v0;//子弹的初速度
	int bWidth,bHeight;//子弹的大小
	enum BulletName bulletName;

};

#endif