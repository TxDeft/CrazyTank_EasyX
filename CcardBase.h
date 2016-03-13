//CcardBase.h
#ifndef _CCARDBASE_H_
#define _CCARDBASE_H_
//include 和 前向引用声明.......................................................................
#include "common.h"



//..............................................................................................

class CcardBase
{
public:
	CcardBase(){cardName=NONAME;}
	virtual void use(CcombatData &combatData,CcombatShower &combatShower)=0; //之后在改成纯虚 ，先让春迪能画
	virtual void throwAway(CcombatData &combatData,CcombatShower &combatShower)=0;

	enum CardName cardName; 
};
#endif