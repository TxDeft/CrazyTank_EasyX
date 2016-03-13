//Ccombatdata.h
#ifndef _CCOMBATDATA_H_
#define _CCOMBATDATA_H_

//include 和 前向引用声明.......................................................................
#include "common.h"



//..............................................................................................


class CcombatData
{
public:
	CcombatData();//主数据的构造函数	
	int initData(CcombatData &combatData);
	int dataRun(CcombatData &combatData,CcombatShower &combatShower);  //启动游戏循环，
	void changeMode();
	void changeCombatStateTo(enum CombatState);
	int getAlivePlayerNum(CcombatData &combatData);

	enum CombatState combatState;//将游戏状态定义为枚举型
	int mode;//0为无调试信息，1为调试
	int whoIsPlaying;//现在的操作权在谁手上
	int playerNum;
	int round;  //当前是第几回合
	Ctank tank[PLAYERNUM_MAX];//定义一个坦克
	CbattleField battleField;

	CbulletBox bulletBox;
	CcardBox cardBox;
};
#endif