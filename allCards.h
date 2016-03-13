//allCards.h
#ifndef _ALLCARDS_H_
#define _ALLCARDS_H_
//include �� ǰ����������.......................................................................
#include "common.h"


//..............................................................................................

//��˲���ӵ�����
class CcardBlink:public CcardBase
{
public:
	CcardBlink();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//��ԭ�ӵ�����
class CcardNuclear:public CcardBase
{
public:
	CcardNuclear();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};

//������������
class CcardGuide:public CcardBase
{
public:
	CcardGuide();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};

//�����ϲʵ�����
class CcardBet:public CcardBase
{
public:
	CcardBet();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//����Ѫ��������
class CcardSx:public CcardBase
{
public:
	CcardSx();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//�����ƿ���
class CcardHeal:public CcardBase
{
public:
	CcardHeal();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//������Ⱥ�ƿ���
class CcardLunaHeal:public CcardBase
{
public:
	CcardLunaHeal();
	void use(CcombatData &combatData,CcombatShower &combatShower);
    void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};

//������װ������
class CcardReload:public CcardBase
{
public:
	CcardReload();
	void use(CcombatData &combatData,CcombatShower &combatShower);
    void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};
//���ױ��ռ俨��
class CcardCritSpace:public CcardBase
{
public:
	CcardCritSpace();
	void use(CcombatData &combatData,CcombatShower &combatShower);
    void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};
//������Ĩɱ����
class CcardCardSweep:public CcardBase
{
public:
	CcardCardSweep();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//�������籩����

class CcardThunderStorm:public CcardBase
{
public:
	CcardThunderStorm();
	void use(CcombatData &combatData,CcombatShower &combatShower);
    void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//���������ݿ���
class CcardBarrier:public CcardBase
{
public:
	CcardBarrier();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};




////��������������������������Ƭ���ӡ�����������������������
class CcardBox
{
public:
	CcardBase *card[MAX_CARD_KIND_NUM+1];
	CcardBlink cardBlink;
	CcardNuclear cardNuclear;
	CcardGuide cardGuide;
	CcardBet cardBet;
	CcardSx cardSx;	
	CcardHeal cardHeal;
	CcardLunaHeal cardLunaHeal;
    CcardReload   cardReload;
	CcardCritSpace cardCritSpace;
	CcardCardSweep  cardCardSweep;
	CcardThunderStorm cardThunderStorm;
	CcardBarrier cardBarrier;

	int cardLeftNum[MAX_CARD_KIND_NUM+1];
	int cardTotalLeftNum;
	int originalCardKind; //�ƶѳ�ʼ����ʱ���Ƶ����������ֵ������enum�зǿտ�Ƭ��������

	CcardBox();
	void addCard(enum CardName cardName,int number);  
	void initCardBox();
	void dealCard(CcombatData &combatData,CcombatShower &combatShower);	
	int sumLeftCardNumBefore(int cardName);   //������ĳһ�ſ�Ƭ֮ǰenum�����е�ʣ�࿨Ƭ������֧��intתö�١���ֻ����ôд�ˡ�
};


#endif