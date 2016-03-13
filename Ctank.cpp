//Ctank.cpp

//include �� ǰ����������.......................................................................
#include "common.h"
#include"Ctank.h"
using namespace std;



//..............................................................................................

Ctank::Ctank()
{
	tkWidth=TANKWIDTH;
	tkHeight=TANKHEIGHT;

	tankCita=0;
	launchCita=PI/4;
	launchStrength=0;
	energy=100;
	hp=100;
	hpChange=0;
	gotDoubleDamage=false;
	timer=TIMELMT;
	clockBreak=0;
	alreadyLaunch=false;

	bullet=NULL;

	cardUsingIndex=0; //����ʹ�õĿ�Ƭ��orѡ��ʹ�õĿ�Ƭ
	cntHandCardNum=0;//��ǰ������
	for(int i=0;i<MAX_HANDCARD_NUM+1;i++)
	{
		myCards[i]=NULL;
	}
}

void Ctank::setLocation(Cpoint &pLocation)//tank��λ�����ú���
{
	int k=rand()%2;
	//cout<<"��k��="<<k<<endl;
	tankDirection=(k==0)? -1:1;
	position.x=pLocation.x;
	position.y=pLocation.y;
}

int Ctank::controller(CcombatData &combatData,CcombatShower &combatShower)//����Tank�Ŀ��ƺ���
{   
	alreadyLaunch=false;
	time_t startS,finishS;//���忪ʼʱ��ʱ���Լ�����ʱ��ʱ�䣻
	clock_t startBreak,finishBreak;
	startS=time(NULL);
	char control=NULL;
				
	//cout<<"Round:"<<combatData.round<<"��tank"<<combatData.whoIsPlaying<<"��������"<<cntHandCardNum<<endl;
	while(hp>0)
	{   
		combatShower.show(combatData);  //����Ϸ�Ĵ󲿷�ʱ����������������������ﲻ����Ұ�������������һ�顣�����Ϳ��������涨��һ�ױ���������
		control=NULL;//һ��Ҫ���
		while(kbhit())
		{
			control=getch();
		}
		switch(control)
		{
		case'K'://�������
			tankDirection=-1;//����
			translateMove(-1*(int)DMOVE,combatData,combatShower);
			break;
		case'M'://�������
			tankDirection=1;//����
			translateMove((int)DMOVE,combatData,combatShower);
			break;
		case'P'://�������
			dChangeCita(-DCITA );
			break;
		case'H'://�������
			dChangeCita(DCITA );
			break;
		case';'://F1
			if(myCards[1]!=NULL)
			{
				cardUsingIndex=1;
				myCards[1]->use(combatData,combatShower);
				if(myCards[cardUsingIndex]->cardName==BLINK 
				  || myCards[cardUsingIndex]->cardName==NUCLEAR 
				  || myCards[cardUsingIndex]->cardName==GUIDE 
				  || myCards[cardUsingIndex]->cardName==BET
				  || myCards[cardUsingIndex]->cardName==SX){goto lable_launch;}
			}
			break;
		case'<'://F2
			if(myCards[2]!=NULL)
			{
				cardUsingIndex=2;
				myCards[2]->use(combatData,combatShower);
				if(myCards[cardUsingIndex]->cardName==BLINK 
				  || myCards[cardUsingIndex]->cardName==NUCLEAR 
				  || myCards[cardUsingIndex]->cardName==GUIDE 
				  || myCards[cardUsingIndex]->cardName==BET
				  || myCards[cardUsingIndex]->cardName==SX){goto lable_launch;}
			}
			break;
		case'='://F3
			if(myCards[3]!=NULL)
			{
				cardUsingIndex=3;
				myCards[3]->use(combatData,combatShower);
				if(myCards[cardUsingIndex]->cardName==BLINK 
				  || myCards[cardUsingIndex]->cardName==NUCLEAR 
				  || myCards[cardUsingIndex]->cardName==GUIDE 
				  || myCards[cardUsingIndex]->cardName==BET
				  || myCards[cardUsingIndex]->cardName==SX){goto lable_launch;}
			}
			break;
		case'>'://F4
			if(myCards[4]!=NULL)
			{
				cardUsingIndex=4;
				myCards[4]->use(combatData,combatShower);			
				if(myCards[cardUsingIndex]->cardName==BLINK 
				  || myCards[cardUsingIndex]->cardName==NUCLEAR 
				  || myCards[cardUsingIndex]->cardName==GUIDE 
				  || myCards[cardUsingIndex]->cardName==BET
				  || myCards[cardUsingIndex]->cardName==SX){goto lable_launch;}
			}
			break;
		case' '://�ո�
lable_launch:
			//clockBreak=0;
			startBreak=clock();
			if(alreadyLaunch==false && energy>=1)
			{
				while(launchStrength<0.5)   //���������²��ܷ���
				{
					saveLaunchStrength(combatData,combatShower);
				}
				launch(combatData,combatShower);
				launchStrength=0;//����������ֻع�Ϊ��
				alreadyLaunch=true;
			}
			finishBreak=clock();
			clockBreak+=(double)(0.001*(finishBreak-startBreak));
			break;
		case 'T':
		case't':
			combatData.changeMode();
			break;
		case'C':
		case'c':
			startBreak=clock();
			goto lable_console;
		case 27: //ESC
			startBreak=clock();
			goto lable_menu;
			break;
		case'e':
		case'E':
			combatData.changeCombatStateTo(PLAYER_END_STAGE);
			break;
		default:
			break;
lable_back:
			finishBreak=clock();
			clockBreak+=(double)(0.001*(finishBreak-startBreak));
			break;
		}

		//�����ʹ�ÿ�Ƭ�˾�throw����
		if(cardUsingIndex!=0)
		{
			myCards[cardUsingIndex]->throwAway(combatData,combatShower);
			for(int i=cardUsingIndex;i<cntHandCardNum;i++)
			{
				myCards[i]=myCards[i+1];
			}
			myCards[cntHandCardNum]=NULL;
			cntHandCardNum--;
			cardUsingIndex=0;
		}


		//������ʣ��ʱ�䡿
		finishS=time(NULL);
		double timer1=double(finishS-startS-clockBreak);//���ڼ�¼����ʱ��
		//clockBreak=0;                                          //������������������������������������ʱ�仹�����⡿����������������������������������
		if(timer1<TIMELMT)
		{  
			timer=TIMELMT-timer1;
			//cout<<"ʱ��"<<timer<<endl;
		}
		else
		{
			//cout<<"����ʱ���Ѿ��þ�"<<endl;
			clockBreak=0;  //ÿ�غϽ�����ʱ���þ�
			timer=TIMELMT;
			combatData.changeCombatStateTo(PLAYER_END_STAGE);
		}

		//����Ϸ״̬���ġ�
		if(combatData.combatState==BREAK){/*����gameProcessor�Ķ���������һ����壬�������������˳���Ϸ���������¿�ʼ��*/}
		else if(combatData.combatState!=ACTING_STAGE){clockBreak=0;break;}
	}
	return 0;

lable_console:
	closegraph();
	system("pause");
	initgraph(BFWIDTH,BFHEIGHT);
	HWND hWnd1 = GetHWnd();
	SetWindowText(hWnd1, "ս����...�����̹��DIY�� Made by SAT");
	goto lable_back;

lable_menu:
	startBreak=clock();
	system("cls");
	closegraph();
	char menuControl=NULL;
	HWND hWnd2 = GetHWnd();
	for(;;)
	{
		system("cls");
		cout<<"                      ����ӭ����Menu���桿"<<endl
			<<"SAT:��Ϊ����Ա�����Ǳ�ʾ�����Ǹ�ע���㷨,����������á��ڿ����"<<endl
			<<"-------------------------------------------------------------------"<<endl
			<<"1.����Ϸ˵����"<<endl
			<<"2.���������ǡ�"<<endl
			<<"3.���˳�ս����"<<endl
			<<"4.���˳���Ϸ��"<<endl
			<<"5.������ս����"<<endl
			<<"-------------------------------------------------------------------"<<endl
			<<"ף��Ϸ��죡                                by Steven Apple Trendy "<<endl;
		menuControl=getch();
		switch(menuControl)
		{
			case'1':
				system("cls");
				initgraph(BFWIDTH,BFHEIGHT);
				loadimage(NULL,"res\\picture\\introduction\\introduction1.bmp",BFWIDTH,BFHEIGHT);
				getch();
				loadimage(NULL,"res\\picture\\introduction\\introduction2.bmp",BFWIDTH,BFHEIGHT);
				getch();
				loadimage(NULL,"res\\picture\\introduction\\introduction3.bmp",BFWIDTH,BFHEIGHT);
				getch();
				closegraph();
				break;
			case'2':
				system("cls");
				cout<<"���ǵġ�СС���ܹ�ʦ��"<<endl
					<<"                     �Ƴ�𢣺Steven����һ���Ȱ���̵��к�"<<endl
					<<"                               ���������ǻۣ�Ϊ���ǵ���Ϸ������صĹ���"<<endl
					<<endl
					<<"���ǵġ�СС'����Ա:"<<endl
					<<"                     ����Ƽ��Apple����һ���Ȱ���̵�Ů��"<<endl
					<<"                              ���������ڷܣ�Ϊ���ǵ���Ϸ�������ʵ�Ԫ��"<<endl
					<<endl
					<<"���ǵġ�СС��ͼ�δ�ʦ��"<<endl
					<<"                      �����ϣ�Trendy������һ���Ȱ���̵��к�"<<endl
					<<"                               ��������ͼ��֪ʶ�����ǵ���Ϸ�����Ӿ��ĳ��"<<endl
					<<endl
					<<endl
					<<" We are S.A.T !!!         We are S.A.T!!!             "<<endl
					<<endl
					<<"�������а�������112����Ŷӣ��ڱ�̵ĵ�·�ϣ����ǻ�һֱ����ȥ�����ǻ�һֱ���ͣ�"<<endl
					<<endl
					<<endl
					<<"�����ڴ����Ǹ��Ӿ��ʵİ汾"<<endl
					<<endl;
				system("pause");
				break;
			case'3':
				combatData.changeCombatStateTo(COMBAT_END);
				goto lable_back;
				break;
			case'4':
				combatShower.end_Cartoon(combatData);
				exit(0);
				break;
			case 27:  //ESC
			case'5':
				system("cls");
				initgraph(BFWIDTH,BFHEIGHT);
				SetWindowText(hWnd2, "ս����...�����̹��DIY�� Made by SAT");
				goto lable_back;
				break;
			default:
				break;
		}
	}
}

void  Ctank::translateMove(int dm,CcombatData &combatData,CcombatShower &combatShower)//tank������ת��������ʵ��
{
	double tankCitaXp;//tank��X+�н�
	if(tankDirection==1) //����
	{
		tankCitaXp=tankCita;
	}
	else //����
	{
		tankCitaXp=-tankCita;
	}
	double c=combatData.battleField.getUpSurfaceCita(Cpoint(position.x,combatData.battleField.getUpSurfaceY(position,combatData)),combatData);
	tankCita=(tankDirection==1)? c:(-c);
	if(tankCita<MAXMOVABLECITA && energy>0)  //�ж��Ƿ�ɶ�
	{
		if(changePositionTo(position.x+dm*cos(tankCitaXp),position.y+dm*sin(tankCitaXp)))
		{
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			changeEnergyTo((int)(energy-1));
		}
	}
}

void Ctank::dChangeCita(double Cita)
{
	if(launchCita+Cita<TANK_MAX_LAUNCH_CITA && launchCita+Cita>0)  //launchCita����� tank������ڵļнǣ�
	{
		launchCita+=Cita;
	}
}

int Ctank::launch(CcombatData &combatData, CcombatShower & combatShower)
{   
	//clock_t start,finish;
    //start=clock();
	//cout<<"��launch������"<<endl;
	bullet->createBullet(combatData);
	bullet->fly(combatData,combatShower);
	if(bullet->exist==0)
	{   
		//cout<<"��ǰ����Ϊ"<<energy<<endl;
		launchStrength=0;
	}
	//finish=clock();
	//clockt+=(int)(0.001*(finish-start));
	return 0;
}

int  Ctank::saveLaunchStrength(CcombatData &combatData,CcombatShower & combatShower)
{   
	//cout<<"��������ѭ������"<<endl;
	char control=NULL;
    while(1)
	{      
		if(1/*GetInputState*/)
		{		
			//cout<<"��ʼ����ѭ��"<<endl;
			control=getch();
		}
		else break;
		if((control==' ') && launchStrength<100 && energy>0)
		{
			//cout<<"����ѭ���м�⵽L"<<endl;
			launchStrength+=3;
			changeEnergyTo((int)(energy-3));
			if(launchStrength>100){launchStrength=100;}
		}
		/*if(WM_KEYUP)break;*/
		//'if(!GetInputState)break;
		else if(control==13/*�س�*/){break;}
		else{;}
		combatShower.show(combatData);
		control=NULL;
	}
    return 0;
}
	
int Ctank::changePositionTo(double newX, double newY)
{   
	if(newX<0 || newX>=BFWIDTH || newY<0)  //y�������ޣ������ɵ����Ͽ��Ի���
	{
		return 0;
	}
	else
	{
		position.reset(newX,newY);return 1;
	}
}

int Ctank::changeHpTo(int newHp,CcombatData &combatData,CcombatShower & combatShower)
{  
	hpChange=(newHp>100)? (int)(100-hp):(int)(newHp-hp);
	if(newHp<1)
	{
		newHp=0;
	}
	if(newHp>100)
	{
		newHp=100;
	}
	hp=newHp;
	combatShower.show(combatData);
	if(gotDoubleDamage==true)
	{
		Sleep(800);   //����ͣ�õ�
	}
	else
	{
		Sleep(500);//ͣһ��Ϊ�˿�����Ѫ��
	}
	hpChange=0;
	return 0;
}
int Ctank::changeEnergyTo(int newE)
{
	if(newE<0)
	{
		newE=0;
	}
	if(newE>100)
	{
		newE=100;
	}
	energy=newE;
	return 0;
}
