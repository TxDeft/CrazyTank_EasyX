//CcardBase.h
#ifndef _CCARDBASE_H_
#define _CCARDBASE_H_
//include �� ǰ����������.......................................................................
#include "common.h"



//..............................................................................................

class CcardBase
{
public:
	CcardBase(){cardName=NONAME;}
	virtual void use(CcombatData &combatData,CcombatShower &combatShower)=0; //֮���ڸĳɴ��� �����ô����ܻ�
	virtual void throwAway(CcombatData &combatData,CcombatShower &combatShower)=0;

	enum CardName cardName; 
};
#endif