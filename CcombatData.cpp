//Ccombatdata.cpp
//include 和 前向引用声明.......................................................................
#include "common.h"
#include"CcombatData.h"
using namespace std;

int PLAYERNUM;

//..............................................................................................


CcombatData::CcombatData()
{
	 playerNum=PLAYERNUM;
	 combatState=COMBAT_INITIAL;
	 round=0;
	 whoIsPlaying=-1;
	 mode=0;
}

int CcombatData::initData(CcombatData &combatData)
{
	
	//数据初始化
	changeCombatStateTo(COMBAT_INITIAL);
	battleField.initMap(combatData);
	for(int i=0;i<PLAYERNUM;i++)
	{
		//这里结合地图数组有2的位置，做成随机落地
		int initX,initY=BFHEIGHT-2;
		double k=1.2;
		int range=(int)(BFWIDTH/k);
		for(;;)
		{
			initX=rand()%range+(BFWIDTH-range)/2;
			if(combatData.battleField.getUpSurfaceY(Cpoint(initX,initY),combatData)>0)
			{
				break;
			}
		}
		tank[i].setLocation(Cpoint(initX,initY));    
	}
	bulletBox.initTankBullet(combatData);
	cardBox.initCardBox();
	return 1;
}

int CcombatData::dataRun(CcombatData &combatData,CcombatShower &combatShower)//【【正在修改】】】
{
	for(round=1;combatState!=COMBAT_END;round++)   //controller可以改combatState，比如暂停，退出……  如果有个坦克死了，combatState也会变成某个特定值。
	{	
		combatState=ROUND_START_STAGE;
		combatShower.show(combatData);
		for(int i=0;i<playerNum && combatState!=COMBAT_END;i++)
		{   
			if(combatData.tank[i].hp>=1)//判断坦克是否消亡
			{
				changeCombatStateTo(PLAYER_START_STAGE);
				whoIsPlaying=i;
				tank[whoIsPlaying].energy=100;
				tank[whoIsPlaying].timer=TIMELMT;
				combatShower.show(combatData);
				getch();
				changeCombatStateTo(DEAL_CARD_STAGE);
				combatData.cardBox.dealCard(combatData,combatShower);
				tank[whoIsPlaying].changeHpTo(tank[whoIsPlaying].hp+HPBONUS,combatData,combatShower);
				combatState=ACTING_STAGE;
				tank[whoIsPlaying].controller(combatData,combatShower);
				if(getAlivePlayerNum(combatData)<=1)
				{
					changeCombatStateTo(COMBAT_END);
				}
				if(combatData.combatState==COMBAT_END)
				{
					combatShower.show(combatData);
				}
			}
		}	

	}
	return 0;
}


void CcombatData::changeMode()
{
	if(mode==0)
	{
		mode=1;
	}
	else
	{
		mode=0;
	}
}

void CcombatData::changeCombatStateTo(enum CombatState newState)
{
	combatState=newState;
}

int CcombatData::getAlivePlayerNum(CcombatData &combatData)
{
	int aliveNum=0;
	for(int i=0;i<PLAYERNUM;i++)
	{
		if(combatData.tank[i].hp>0.5){aliveNum++;}
	}
	return aliveNum;
}

