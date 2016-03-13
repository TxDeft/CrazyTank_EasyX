//Ctank.cpp

//include 和 前向引用声明.......................................................................
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

	cardUsingIndex=0; //正在使用的卡片，or选择使用的卡片
	cntHandCardNum=0;//当前手牌数
	for(int i=0;i<MAX_HANDCARD_NUM+1;i++)
	{
		myCards[i]=NULL;
	}
}

void Ctank::setLocation(Cpoint &pLocation)//tank的位置设置函数
{
	int k=rand()%2;
	//cout<<"【k】="<<k<<endl;
	tankDirection=(k==0)? -1:1;
	position.x=pLocation.x;
	position.y=pLocation.y;
}

int Ctank::controller(CcombatData &combatData,CcombatShower &combatShower)//定义Tank的控制函数
{   
	alreadyLaunch=false;
	time_t startS,finishS;//定义开始时的时间以及结束时的时间；
	clock_t startBreak,finishBreak;
	startS=time(NULL);
	char control=NULL;
				
	//cout<<"Round:"<<combatData.round<<"【tank"<<combatData.whoIsPlaying<<"】手牌数"<<cntHandCardNum<<endl;
	while(hp>0)
	{   
		combatShower.show(combatData);  //【游戏的大部分时间是在运行这个函数，这里不管玩家按不按键，都画一遍。这样就可以在里面定义一套背景动画。
		control=NULL;//一定要清空
		while(kbhit())
		{
			control=getch();
		}
		switch(control)
		{
		case'K'://方向键左
			tankDirection=-1;//朝左
			translateMove(-1*(int)DMOVE,combatData,combatShower);
			break;
		case'M'://方向键右
			tankDirection=1;//朝右
			translateMove((int)DMOVE,combatData,combatShower);
			break;
		case'P'://方向键下
			dChangeCita(-DCITA );
			break;
		case'H'://方向键上
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
		case' '://空格
lable_launch:
			//clockBreak=0;
			startBreak=clock();
			if(alreadyLaunch==false && energy>=1)
			{
				while(launchStrength<0.5)   //必须蓄力下才能发炮
				{
					saveLaunchStrength(combatData,combatShower);
				}
				launch(combatData,combatShower);
				launchStrength=0;//发射后力量又回归为零
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

		//【如果使用卡片了就throw掉】
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


		//【计算剩余时间】
		finishS=time(NULL);
		double timer1=double(finishS-startS-clockBreak);//用于记录已用时间
		//clockBreak=0;                                          //【【【【【【【【【【【【【【【【【【时间还有问题】】】】】】】】】】】】】】】】】】
		if(timer1<TIMELMT)
		{  
			timer=TIMELMT-timer1;
			//cout<<"时间"<<timer<<endl;
		}
		else
		{
			//cout<<"您的时间已经用尽"<<endl;
			clockBreak=0;  //每回合结束后时间用尽
			timer=TIMELMT;
			combatData.changeCombatStateTo(PLAYER_END_STAGE);
		}

		//【游戏状态更改】
		if(combatData.combatState==BREAK){/*调用gameProcessor的东西，弹出一个面板，“帮助”，“退出游戏”，“重新开始”*/}
		else if(combatData.combatState!=ACTING_STAGE){clockBreak=0;break;}
	}
	return 0;

lable_console:
	closegraph();
	system("pause");
	initgraph(BFWIDTH,BFHEIGHT);
	HWND hWnd1 = GetHWnd();
	SetWindowText(hWnd1, "战斗中...【疯狂坦克DIY】 Made by SAT");
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
		cout<<"                      【欢迎来到Menu界面】"<<endl
			<<"SAT:身为程序员的我们表示，我们更注重算法,所以这个就用“黑框框”啦"<<endl
			<<"-------------------------------------------------------------------"<<endl
			<<"1.【游戏说明】"<<endl
			<<"2.【关于我们】"<<endl
			<<"3.【退出战斗】"<<endl
			<<"4.【退出游戏】"<<endl
			<<"5.【返回战斗】"<<endl
			<<"-------------------------------------------------------------------"<<endl
			<<"祝游戏愉快！                                by Steven Apple Trendy "<<endl;
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
				cout<<"我们的“小小”架构师："<<endl
					<<"                     闫承稷：Steven——一个热爱编程的男孩"<<endl
					<<"                               他用他的智慧，为我们的游戏引入独特的功能"<<endl
					<<endl
					<<"我们的“小小'程序员:"<<endl
					<<"                     张亚萍：Apple——一个热爱编程的女孩"<<endl
					<<"                              她用她的勤奋，为我们的游戏添入新鲜的元素"<<endl
					<<endl
					<<"我们的“小小”图形大师："<<endl
					<<"                      刘春迪：Trendy——另一个热爱编程的男孩"<<endl
					<<"                               他用他的图形知识，我们的游戏加入视觉的冲击"<<endl
					<<endl
					<<endl
					<<" We are S.A.T !!!         We are S.A.T!!!             "<<endl
					<<endl
					<<"我们是有爱的试验112班的团队，在编程的道路上，我们会一直走下去，我们会一直加油！"<<endl
					<<endl
					<<endl
					<<"敬请期待我们更加精彩的版本"<<endl
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
				SetWindowText(hWnd2, "战斗中...【疯狂坦克DIY】 Made by SAT");
				goto lable_back;
				break;
			default:
				break;
		}
	}
}

void  Ctank::translateMove(int dm,CcombatData &combatData,CcombatShower &combatShower)//tank的坐标转换函数的实现
{
	double tankCitaXp;//tank和X+夹角
	if(tankDirection==1) //朝右
	{
		tankCitaXp=tankCita;
	}
	else //朝左
	{
		tankCitaXp=-tankCita;
	}
	double c=combatData.battleField.getUpSurfaceCita(Cpoint(position.x,combatData.battleField.getUpSurfaceY(position,combatData)),combatData);
	tankCita=(tankDirection==1)? c:(-c);
	if(tankCita<MAXMOVABLECITA && energy>0)  //判断是否可动
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
	if(launchCita+Cita<TANK_MAX_LAUNCH_CITA && launchCita+Cita>0)  //launchCita存的是 tank正向和炮的夹角！
	{
		launchCita+=Cita;
	}
}

int Ctank::launch(CcombatData &combatData, CcombatShower & combatShower)
{   
	//clock_t start,finish;
    //start=clock();
	//cout<<"进launch函数内"<<endl;
	bullet->createBullet(combatData);
	bullet->fly(combatData,combatShower);
	if(bullet->exist==0)
	{   
		//cout<<"当前能量为"<<energy<<endl;
		launchStrength=0;
	}
	//finish=clock();
	//clockt+=(int)(0.001*(finish-start));
	return 0;
}

int  Ctank::saveLaunchStrength(CcombatData &combatData,CcombatShower & combatShower)
{   
	//cout<<"进入蓄力循环函数"<<endl;
	char control=NULL;
    while(1)
	{      
		if(1/*GetInputState*/)
		{		
			//cout<<"开始蓄力循环"<<endl;
			control=getch();
		}
		else break;
		if((control==' ') && launchStrength<100 && energy>0)
		{
			//cout<<"蓄力循环中检测到L"<<endl;
			launchStrength+=3;
			changeEnergyTo((int)(energy-3));
			if(launchStrength>100){launchStrength=100;}
		}
		/*if(WM_KEYUP)break;*/
		//'if(!GetInputState)break;
		else if(control==13/*回车*/){break;}
		else{;}
		combatShower.show(combatData);
		control=NULL;
	}
    return 0;
}
	
int Ctank::changePositionTo(double newX, double newY)
{   
	if(newX<0 || newX>=BFWIDTH || newY<0)  //y不设上限，这样飞到天上可以回来
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
		Sleep(800);   //暴击停久点
	}
	else
	{
		Sleep(500);//停一下为了看出掉血量
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
