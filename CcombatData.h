//Ccombatdata.h
#ifndef _CCOMBATDATA_H_
#define _CCOMBATDATA_H_

//include �� ǰ����������.......................................................................
#include "common.h"



//..............................................................................................


class CcombatData
{
public:
	CcombatData();//�����ݵĹ��캯��	
	int initData(CcombatData &combatData);
	int dataRun(CcombatData &combatData,CcombatShower &combatShower);  //������Ϸѭ����
	void changeMode();
	void changeCombatStateTo(enum CombatState);
	int getAlivePlayerNum(CcombatData &combatData);

	enum CombatState combatState;//����Ϸ״̬����Ϊö����
	int mode;//0Ϊ�޵�����Ϣ��1Ϊ����
	int whoIsPlaying;//���ڵĲ���Ȩ��˭����
	int playerNum;
	int round;  //��ǰ�ǵڼ��غ�
	Ctank tank[PLAYERNUM_MAX];//����һ��̹��
	CbattleField battleField;

	CbulletBox bulletBox;
	CcardBox cardBox;
};
#endif