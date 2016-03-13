#include "common.h"
#include"allCards.h"
using namespace std;

//..............................................................................................

//��˲���ӵ�����
CcardBlink::CcardBlink()
{
	cardName=BLINK;
}
void CcardBlink::use(CcombatData &combatData,CcombatShower &combatShower)
{
	combatShower.show(combatData);
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletBlink;
}
void CcardBlink::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletNormal;
}


//��ԭ�ӵ�����
CcardNuclear::CcardNuclear()
{
	cardName=NUCLEAR;
}
void CcardNuclear::use(CcombatData &combatData,CcombatShower &combatShower)
{
	combatShower.show(combatData);
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletNuclear;
}
void CcardNuclear::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletNormal;
}


//������������
CcardGuide::CcardGuide()
{
	cardName=GUIDE;
}
void CcardGuide::use(CcombatData &combatData,CcombatShower &combatShower)
{
	combatShower.show(combatData);
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletGuide;
}
void CcardGuide::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletNormal;
}


//�����ϲʵ�����
CcardBet::CcardBet()
{
	cardName=BET;
}
void CcardBet::use(CcombatData &combatData,CcombatShower &combatShower)
{
	combatShower.show(combatData);
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletBet;
}
void CcardBet::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletNormal;
}

//����Ѫ��������
CcardSx::CcardSx()
{
	cardName=SX;
}
void CcardSx::use(CcombatData &combatData,CcombatShower &combatShower)
{
	combatShower.show(combatData);
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletSx;
}
void CcardSx::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
	combatData.tank[combatData.whoIsPlaying].bullet=&combatData.bulletBox.bulletNormal;
}


//�����ƿ���
CcardHeal::CcardHeal()
{
	cardName=HEAL;
}
void CcardHeal::use(CcombatData &combatData,CcombatShower &combatShower)
{
	combatShower.show(combatData);
	combatData.tank[combatData.whoIsPlaying].changeHpTo((int)combatData.tank[combatData.whoIsPlaying].hp+20,combatData,combatShower);
}
void CcardHeal::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
}

//������Ⱥ�ƿ���

CcardLunaHeal::CcardLunaHeal()
{
	cardName=LUNAHEAL;
}
void CcardLunaHeal::use(CcombatData &combatData,CcombatShower &combatShower)
{    
	int addHp=10;
	combatShower.show(combatData);
	for(int i=0;i<combatData.playerNum;i++)
	{
		  if(combatData.tank[i].hp>0.5)
		  {
			  combatData.tank[i].changeHpTo((int)(combatData.tank[i].hp+addHp),combatData,combatShower);
		  }

	}
}
void  CcardLunaHeal::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
}


//������װ������
CcardReload::CcardReload()
{
	cardName=RELOAD;
}
void CcardReload::use(CcombatData &combatData, CcombatShower &combatShower)
{  
	combatShower.show(combatData);
	combatData.tank[combatData.whoIsPlaying].alreadyLaunch=false;
	//combatData.tank[combatData.whoIsPlaying].timer=30;
	//combatData.tank[combatData.whoIsPlaying].clockBreak=0;
	combatShower.show(combatData);
}
void CcardReload::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
}
	
//���ױ��ռ俨��
CcardCritSpace::CcardCritSpace()
{
	cardName=CRITSPACE;
}
void CcardCritSpace::use(CcombatData &combatData, CcombatShower &combatShower)
{  
	combatShower.show(combatData);
	for(int i=0;i<combatData.playerNum;i++)
    combatData.tank[i].	gotDoubleDamage=true;
}
void CcardCritSpace::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{ 
}

//������Ĩɱ��
CcardCardSweep::CcardCardSweep()
{
	cardName=CARDSWEEP;
}
void CcardCardSweep::use(CcombatData &combatData, CcombatShower &combatShower)
{  
	combatShower.show(combatData);
	for(int i=0;i<combatData.playerNum;i++)
	{
		if(i!=combatData.whoIsPlaying)
        {
		    combatData.tank[i].cntHandCardNum=0;
			for(int j=0;j<MAX_HANDCARD_NUM+1;j++)
			combatData.tank[i].myCards[j]=NULL;
		}
	}
}
void CcardCardSweep::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{

}

//�������籩����
 CcardThunderStorm::CcardThunderStorm()
{
	cardName=THUNDERSTORM;
}
void CcardThunderStorm::use(CcombatData &combatData, CcombatShower &combatShower)
{  
	 int flickDistance=150,range=50;//�������룬������Χ
	 combatShower.show(combatData);
	 double x0=combatData.tank[combatData.whoIsPlaying].position.x;
	 double y0=combatData.tank[combatData.whoIsPlaying].position.y;
	 for(int i=0;i<combatData.playerNum;i++)
	{   
		if(i!=combatData.whoIsPlaying)
		{  
			if(combatData.tank[i].position.dist(combatData.tank[i].position,combatData.tank[combatData.whoIsPlaying].position)<range)
		     {   double  x=combatData.tank[i].position.x;
			     double   y=combatData.tank[i].position.y;
				 double dis=sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0));
					//if(combatData.tank[i].position.x<x0)
					{						if((combatData.tank[i].position.x+(x-x0)/dis*flickDistance)<0)							combatData.tank[i].position.x=0;					    if((combatData.tank[i].position.x+(x-x0)/dis*flickDistance)>BFWIDTH)							combatData.tank[i].position.x=BFWIDTH-1;					    else							combatData.tank[i].position.x+=(x-x0)/dis*flickDistance;                        if((combatData.tank[i].position.y+(y-y0)/dis*flickDistance)<0)							combatData.tank[i].position.y=0;						if((combatData.tank[i].position.y+(y-y0)/dis*flickDistance)>BFHEIGHT)							combatData.tank[i].position.y=BFHEIGHT-1;						//combatData.tank[i].translateMove((-flickDistance),combatData,combatShower);						else						combatData.tank[i].position.y+=(y-y0)/dis*flickDistance;
					}
				   //else

				   //{  
					 //combatData.tank[i].translateMove((flickDistance),combatData,combatShower);
				  // }
		     }
		}
		
	 }
   combatData.battleField.putTankToUpSurface(combatData,combatShower);
}
void CcardThunderStorm::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
}


//���������ݿ���
CcardBarrier::CcardBarrier()
{
	cardName=BARRIER;
}
void CcardBarrier::use(CcombatData &combatData,CcombatShower &combatShower)
{
	int br1=70,br2=90;
	combatShower.show(combatData);
	int xl=(int)combatData.tank[combatData.whoIsPlaying].position.x-br2;
	int xr=(int)combatData.tank[combatData.whoIsPlaying].position.x+br2;
	int yh=(int)combatData.tank[combatData.whoIsPlaying].position.y+br2;
	int yb=(int)combatData.tank[combatData.whoIsPlaying].position.y-br2;
	xl=(xl<0)? 0:xl;
	xr=(xr>=BFWIDTH)? (BFWIDTH-1):xr;
	yh=(yh>=BFHEIGHT)? (BFHEIGHT-1):yh;
	yb=(yb<0)? 0:yb;
	//ֻ��tank��ǰ���
	if(combatData.tank[combatData.whoIsPlaying].tankDirection==1){xl=(int)(combatData.tank[combatData.whoIsPlaying].position.x-0.5*(combatData.tank[combatData.whoIsPlaying].position.x-xl));}
	else{xr=(int)(combatData.tank[combatData.whoIsPlaying].position.x+0.5*(xr-combatData.tank[combatData.whoIsPlaying].position.x));}
	combatData.battleField.startChangeMapValue(xl,yb,xr,yh,combatData);
	for(int i=xl;i<=xr;i++)
	{
		for(int j=yb;j<=yh;j++)
		{
			double d=combatData.tank[combatData.whoIsPlaying].position.dist(combatData.tank[combatData.whoIsPlaying].position,Cpoint(i,j));
			if(d>br1 && d<br2)
			{
				combatData.battleField.changeMapValueTo(i,j,1);
			}
		}
	}
	combatData.battleField.finishChangeMapValue(xl,yb,xr,yh,combatData);
}
void CcardBarrier::throwAway(CcombatData &combatData,CcombatShower &combatShower)
{
}




//��������������������������Ƭ���ӡ�����������������������
CcardBox::CcardBox()
{
	for(int i=0;i<MAX_CARD_KIND_NUM;i++)
	{
		cardLeftNum[i]=0;
	}
	cardTotalLeftNum=0;
}

void CcardBox::addCard(enum CardName cardName,int number)
{
	cardLeftNum[cardName]+=number;
	cardTotalLeftNum+=number;
}

void CcardBox::initCardBox()
{
	//enum���еĿ�Ƭ���붼���
	originalCardKind=12;  //���ֵ������enum�зǿտ�Ƭ������
	card[BLINK]=&cardBlink;
	card[NUCLEAR]=&cardNuclear;
	card[GUIDE]=&cardGuide;
	card[BET]=&cardBet;
	card[SX]=&cardSx;	
	card[HEAL]=&cardHeal;
	card[LUNAHEAL]=&cardLunaHeal;
    card[RELOAD]=&cardReload;
	card[CRITSPACE]=&cardCritSpace;
	card[CARDSWEEP]=&cardCardSweep;
	card[THUNDERSTORM]=&cardThunderStorm;
	card[BARRIER]=&cardBarrier;


	//�ܹ�200��
	addCard(BLINK,30);
	addCard(NUCLEAR,4);
	addCard(GUIDE,30);
	addCard(BET,10);
	addCard(SX,20);
	addCard(HEAL,30);
	addCard(LUNAHEAL,10);
	addCard(RELOAD,20);
	addCard(CRITSPACE,20);
	addCard(CARDSWEEP,10);
	addCard(THUNDERSTORM,6);  //6
	addCard(BARRIER,10);     //10
}

void CcardBox::dealCard(CcombatData &combatData,CcombatShower &combatShower)
{
	if(cardTotalLeftNum>0)
	{
		if(combatData.tank[combatData.whoIsPlaying].cntHandCardNum<4)
		{
			int k=rand()%cardTotalLeftNum;
			for(int i=1;i<=originalCardKind;i++)
			{
				if(k>=sumLeftCardNumBefore(i) && k<sumLeftCardNumBefore(i+1) && cardLeftNum[i]>0)
				{
					combatData.tank[combatData.whoIsPlaying].myCards[combatData.tank[combatData.whoIsPlaying].cntHandCardNum+1]=card[i];
					cardLeftNum[i]--;
					cardTotalLeftNum--;
				}
			}		
			combatData.tank[combatData.whoIsPlaying].cntHandCardNum++;
		}
	}
	combatShower.show(combatData);
}

int CcardBox::sumLeftCardNumBefore(int cardName)   //������ĳһ�ſ�Ƭ֮ǰenum�����е�ʣ�࿨Ƭ������֧��intתö�١���ֻ����ôд�ˡ�
{
	int sum=0;
	for(int i=0;i<cardName;i++)
	{
		sum+=cardLeftNum[i];
	}
	return sum;
}

