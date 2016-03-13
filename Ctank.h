//Ctank.h
#ifndef _CTANK_H_
#define _CTANK_H_

//include �� ǰ����������.......................................................................
#include "common.h"



//..............................................................................................

class Ctank
{
public:
	Ctank();
	void setLocation(Cpoint &pLocation); //����̹�˵�λ��
	int controller(CcombatData &combatData,CcombatShower &combatShower);//̹�˵Ŀ�����
	void translateMove(int dm,CcombatData &combatData,CcombatShower &combatShower);//����λ������ת��
	void dChangeCita(double dCita);//����Ƕ�ת����
	int launch(CcombatData &combatData, CcombatShower & combatShower);//����
	int saveLaunchStrength(CcombatData &combatData,CcombatShower & combatShower);//��������
    int changeHpTo(int newHp,CcombatData &combatData,CcombatShower & combatShower);
	int changeEnergyTo(int newE);
	int changePositionTo(double newX,double newY);
	
	int tkWidth,tkHeight;//̹�˵ĸ߶ȣ����
	Cpoint position;   //̹�˵ױ��е��λ��    ���½���ԭ��
	int tankDirection;  //�� -1�� ��1
	double tankCita;  //̹�˳�ͷ��x�нǣ�-90��90��
	double launchCita;  //�ڿں�̹�˳�ͷ����н� ��0��90�ȣ�
	double launchStrength; //Ӱ��v0  
	double energy; //ÿ�غϿ�ʼ��ʱ������Ϊ100���ƶ��ͼ�������֮
	double hp;//��������Χ�ı�ը��Χ��ʱѪ������
	double timer;
	clock_t clockBreak;//��������������ۼ�ÿһ����launch��ʱ�䡾�������������ݡ�����������
	CbulletBase *bullet;
	bool alreadyLaunch;

	bool gotDoubleDamage; 
	int hpChange;  

	int cardUsingIndex; //����ʹ�õĿ�Ƭ��orѡ��ʹ�õĿ�Ƭ    ��1��ʾ����1����ת�ɡ��˵�˼ά����
	int cntHandCardNum;//��ǰ������
	CcardBase *myCards[MAX_HANDCARD_NUM+1];   //���±�1��ʾ��һ�����ӣ�ת������ϰ�ߵ�˼ά�ˣ���
};

#endif
