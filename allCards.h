//allCards.h
#ifndef _ALLCARDS_H_
#define _ALLCARDS_H_
//include 和 前向引用声明.......................................................................
#include "common.h"


//..............................................................................................

//【瞬移子弹卡】
class CcardBlink:public CcardBase
{
public:
	CcardBlink();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//【原子弹卡】
class CcardNuclear:public CcardBase
{
public:
	CcardNuclear();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};

//【引导弹卡】
class CcardGuide:public CcardBase
{
public:
	CcardGuide();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};

//【六合彩弹卡】
class CcardBet:public CcardBase
{
public:
	CcardBet();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//【嗜血连击卡】
class CcardSx:public CcardBase
{
public:
	CcardSx();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//【治疗卡】
class CcardHeal:public CcardBase
{
public:
	CcardHeal();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//【月神群疗卡】
class CcardLunaHeal:public CcardBase
{
public:
	CcardLunaHeal();
	void use(CcombatData &combatData,CcombatShower &combatShower);
    void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};

//【重新装弹卡】
class CcardReload:public CcardBase
{
public:
	CcardReload();
	void use(CcombatData &combatData,CcombatShower &combatShower);
    void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};
//【易爆空间卡】
class CcardCritSpace:public CcardBase
{
public:
	CcardCritSpace();
	void use(CcombatData &combatData,CcombatShower &combatShower);
    void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};
//【卡牌抹杀卡】
class CcardCardSweep:public CcardBase
{
public:
	CcardCardSweep();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//【雷霆风暴卡】

class CcardThunderStorm:public CcardBase
{
public:
	CcardThunderStorm();
	void use(CcombatData &combatData,CcombatShower &combatShower);
    void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};


//【防御壁垒卡】
class CcardBarrier:public CcardBase
{
public:
	CcardBarrier();
	void use(CcombatData &combatData,CcombatShower &combatShower);
	void throwAway(CcombatData &combatData,CcombatShower &combatShower);
};




////………………………………卡片盒子………………………………
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
	int originalCardKind; //牌堆初始化的时候，牌的种数【这个值必须是enum中非空卡片的总数】

	CcardBox();
	void addCard(enum CardName cardName,int number);  
	void initCardBox();
	void dealCard(CcombatData &combatData,CcombatShower &combatShower);	
	int sumLeftCardNumBefore(int cardName);   //计算在某一张卡片之前enum序列中的剩余卡片数【不支持int转枚举……只好这么写了】
};


#endif