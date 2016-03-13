//CbulletBase.h
#ifndef _CBULLETBASE_H_
#define _CBULLETBASE_H_

//include �� ǰ����������.......................................................................
#include "common.h"



//..............................................................................................

class CbulletBase
{
public:
	CbulletBase();//�ӵ��Ĺ��캯��
	void createBullet(CcombatData &combatData);
	void eliminateBullet();//��� ֻ�ı�exsit��ֵ����������Ҫ�� 
    int changePositionTo(double newx,double newy);
	bool judgeCollision(int x,int y,CcombatData & combatData);  //��ײ�˷���true
	
	virtual void bomb(CcombatData &combatData,CcombatShower &combatShower);//�ӵ��ı�ը���ݰ�����������
    virtual void fly(CcombatData &combatData,CcombatShower &combatShower);//�ӵ����ƶ����� 

	bool exist;//=0;//���������ڵ��Ƿ����
	bool bombOrNot;//���ڼ���Ƿ�ը��
	Cpoint position;//�ӵ���ǰ���λ��
	double v0;//�ӵ��ĳ��ٶ�
	int bWidth,bHeight;//�ӵ��Ĵ�С
	enum BulletName bulletName;

};

#endif