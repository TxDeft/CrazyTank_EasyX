//allBullets.h
#ifndef _ALLBULLETS_H_
#define _ALLBULLETS_H_

//include 和 前向引用声明.......................................................................
#include "common.h"



//..............................................................................................

//【普通子弹】
class CbulletNormal: public CbulletBase
{
public:
	CbulletNormal();//子弹的构造函数
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//子弹的爆炸数据包传来的数据
	void fly(CcombatData &combatData,CcombatShower &combatShower);//子弹的移动函数  
};

//【瞬移子弹】
class CbulletBlink: public CbulletBase
{
public:
	CbulletBlink();//子弹的构造函数
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//子弹的爆炸数据包传来的数据
	void fly(CcombatData &combatData,CcombatShower &combatShower);//子弹的移动函数  
};


//【原子弹】
class CbulletNuclear: public CbulletBase
{
public:
	CbulletNuclear();//子弹的构造函数
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//子弹的爆炸数据包传来的数据
	void fly(CcombatData &combatData,CcombatShower &combatShower);//子弹的移动函数  
};


//【引导炮弹】
class CbulletGuide: public CbulletBase
{
public:
	CbulletGuide();
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//子弹的爆炸数据包传来的数据
	void fly(CcombatData &combatData,CcombatShower &combatShower);//子弹的移动函数  
};

//【六合彩弹】
class CbulletBet: public CbulletBase
{
public:
	CbulletBet();
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//子弹的爆炸数据包传来的数据
	void fly(CcombatData &combatData,CcombatShower &combatShower);//子弹的移动函数  
};

//【嗜血连发弹】
class CbulletSx: public CbulletBase
{
public:
	CbulletSx();
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//子弹的爆炸数据包传来的数据
	void fly(CcombatData &combatData,CcombatShower &combatShower);//子弹的移动函数  
};


//……………………子弹盒子……………………
class CbulletBox
{
public:
	CbulletNormal bulletNormal;
	CbulletBlink bulletBlink;
	CbulletNuclear bulletNuclear;
	CbulletGuide bulletGuide;
	CbulletBet bulletBet;
	CbulletSx bulletSx;

	void initTankBullet(CcombatData & combatData);
};


#endif