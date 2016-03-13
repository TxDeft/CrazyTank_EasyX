//allBullets.h
#ifndef _ALLBULLETS_H_
#define _ALLBULLETS_H_

//include �� ǰ����������.......................................................................
#include "common.h"



//..............................................................................................

//����ͨ�ӵ���
class CbulletNormal: public CbulletBase
{
public:
	CbulletNormal();//�ӵ��Ĺ��캯��
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//�ӵ��ı�ը���ݰ�����������
	void fly(CcombatData &combatData,CcombatShower &combatShower);//�ӵ����ƶ�����  
};

//��˲���ӵ���
class CbulletBlink: public CbulletBase
{
public:
	CbulletBlink();//�ӵ��Ĺ��캯��
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//�ӵ��ı�ը���ݰ�����������
	void fly(CcombatData &combatData,CcombatShower &combatShower);//�ӵ����ƶ�����  
};


//��ԭ�ӵ���
class CbulletNuclear: public CbulletBase
{
public:
	CbulletNuclear();//�ӵ��Ĺ��캯��
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//�ӵ��ı�ը���ݰ�����������
	void fly(CcombatData &combatData,CcombatShower &combatShower);//�ӵ����ƶ�����  
};


//�������ڵ���
class CbulletGuide: public CbulletBase
{
public:
	CbulletGuide();
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//�ӵ��ı�ը���ݰ�����������
	void fly(CcombatData &combatData,CcombatShower &combatShower);//�ӵ����ƶ�����  
};

//�����ϲʵ���
class CbulletBet: public CbulletBase
{
public:
	CbulletBet();
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//�ӵ��ı�ը���ݰ�����������
	void fly(CcombatData &combatData,CcombatShower &combatShower);//�ӵ����ƶ�����  
};

//����Ѫ��������
class CbulletSx: public CbulletBase
{
public:
	CbulletSx();
	void bomb(CcombatData &combatData,CcombatShower &combatShower);//�ӵ��ı�ը���ݰ�����������
	void fly(CcombatData &combatData,CcombatShower &combatShower);//�ӵ����ƶ�����  
};


//�����������������ӵ����ӡ���������������
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