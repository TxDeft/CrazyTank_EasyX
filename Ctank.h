//Ctank.h
#ifndef _CTANK_H_
#define _CTANK_H_

//include 和 前向引用声明.......................................................................
#include "common.h"



//..............................................................................................

class Ctank
{
public:
	Ctank();
	void setLocation(Cpoint &pLocation); //设置坦克的位置
	int controller(CcombatData &combatData,CcombatShower &combatShower);//坦克的控制器
	void translateMove(int dm,CcombatData &combatData,CcombatShower &combatShower);//用于位置坐标转换
	void dChangeCita(double dCita);//发射角度转换器
	int launch(CcombatData &combatData, CcombatShower & combatShower);//发射
	int saveLaunchStrength(CcombatData &combatData,CcombatShower & combatShower);//蓄力函数
    int changeHpTo(int newHp,CcombatData &combatData,CcombatShower & combatShower);
	int changeEnergyTo(int newE);
	int changePositionTo(double newX,double newY);
	
	int tkWidth,tkHeight;//坦克的高度，宽度
	Cpoint position;   //坦克底边中点的位置    左下角是原点
	int tankDirection;  //左 -1； 右1
	double tankCita;  //坦克车头和x夹角（-90，90）
	double launchCita;  //炮口和坦克车头方向夹角 （0，90度）
	double launchStrength; //影响v0  
	double energy; //每回合开始的时候重置为100，移动和技能消耗之
	double hp;//在其他范围的爆炸范围内时血量减少
	double timer;
	clock_t clockBreak;//定义此数据用于累加每一调用launch的时间【【【【增加数据】】】】】】
	CbulletBase *bullet;
	bool alreadyLaunch;

	bool gotDoubleDamage; 
	int hpChange;  

	int cardUsingIndex; //正在使用的卡片，or选择使用的卡片    【1表示格子1】，转成【人的思维】了
	int cntHandCardNum;//当前手牌数
	CcardBase *myCards[MAX_HANDCARD_NUM+1];   //【下标1表示第一个格子，转换成人习惯的思维了！】
};

#endif
