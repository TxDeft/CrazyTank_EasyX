//【【【【【Qusetion！】】】】】tank hp改成 int 似乎有问题……为毛会画出那么长个血条……   画图地方 int不行？

//进入游戏：读取，主界面：{开始游戏，选项（有个选项是否录像），回放，游戏说明，关于我们，退出}
//游戏中，BREAK {游戏说明，返回主界面，重新开始，退出游戏}

//CgameProcessor.cpp
//include 和 前向引用声明.......................................................................
#include "common.h"
#include"CgameProcessor.h"
using namespace std;
extern int PLAYERNUM;

//..............................................................................................

CgameProcessor::CgameProcessor()
{
	for(int i=0;i<MAX_PROCESS_NUM;i++)
	{
		gameProcesses[i]=NOPROCESS;   //0是最开始的NOPROCESS预设的，用于第一次离开…… 0-9都是后期可用的PROCESS。
	}
	cntProcessStep=0;
}

void CgameProcessor::changeGameProcessTo(enum GameProcess newGP)          //【概念明确】cnt指的是已经添加进去的的当前位置。还没完全退出的不算。已经进去的算
{
	int p=findExistProcess(newGP);
	if(p!=-1) //【跳回已存在的流程处】
	{
		for(int i=cntProcessStep;i>p;i--)   //退回到重复位置
		{
			switch(gameProcesses[i])     
			{
				case NOPROCESS:cout<<"leave NOPROCESS"<<endl;break;
				case LOADING:loading_controller(0);break;
				case MAIN_UI:main_ui_controller(0);break;
				case START_COMBAT:start_combat_controller(0);break;
				case COMBAT:combat_controller(0);break;
				case COMBAT_BREAK:combat_break_controller(0);break;
				case EXIT:exit_controller(0);break;
				case OPTION:option_controller(0);break;
				//……
				default:break;
			}
			gameProcesses[i]=NOPROCESS;
		}
		cntProcessStep=p;
		switch(gameProcesses[p])     
		{
			case NOPROCESS:cout<<"to NOPROCESS"<<endl;break;
			case LOADING:loading_controller(1);break;
			case MAIN_UI:main_ui_controller(1);break;
			case START_COMBAT:start_combat_controller(1);break;
			case COMBAT:combat_controller(1);break;
			case COMBAT_BREAK:combat_break_controller(1);break;
			case EXIT:exit_controller(1);break;
			case OPTION:option_controller(1);break;
			//……
			default:break;
		}
	}

	else //【添加一个没有的新流程】
	{
		//1.离开就旧流程
		switch(gameProcesses[cntProcessStep])   
		{
			case NOPROCESS:cout<<"leave NOPROCESS"<<endl;break;
			case LOADING:loading_controller(0);break;
			case MAIN_UI:main_ui_controller(0);break;
			case START_COMBAT:start_combat_controller(0);break;
			case COMBAT:combat_controller(0);break;
			case COMBAT_BREAK:combat_break_controller(0);break;
			case EXIT:exit_controller(0);break;
			case OPTION:option_controller(0);break;
			//……
			default:break;
		}
		//2.进入新流程
		cntProcessStep++;
		gameProcesses[cntProcessStep]=newGP;
		switch(newGP)     
		{
			case NOPROCESS:cout<<"to NOPROCESS"<<endl;break;
			case LOADING:loading_controller(1);break;
			case MAIN_UI:main_ui_controller(1);break;
			case START_COMBAT:start_combat_controller(1);break;
			case COMBAT:combat_controller(1);break;
			case COMBAT_BREAK:combat_break_controller(1);break;
			case EXIT:exit_controller(1);break;
			case OPTION:option_controller(1);break;
			//……
			default:break;
		}
	}	
}

int CgameProcessor::findExistProcess(enum GameProcess GP)   //【找一个流程明，并返回其下标。  无的时候返回-1】
{
	for(int i=0;i<=cntProcessStep;i++)
	{
		if(gameProcesses[i]==GP){return i;}
	}
	return -1;
}


void CgameProcessor::loading_controller(int to1_leave0)
{
	if(to1_leave0==0)//【要离开此状态】
	{
		//画个画：以加载完毕，按任意键继续。
		cout<<"finish loading,press any button to continue"<<endl;
		getch();
		cout<<"leave loading"<<endl;
	}
	else  //【要进入此状态,并开始执行此状态下的控制代码】
	{	
		cout<<"to loading"<<endl;
		//画个loading的画
		cout<<"now loading..."<<endl;
		Sleep(1000);//做个假象- -
	}
}

void CgameProcessor::main_ui_controller(int to1_leave0)
{
	if(to1_leave0==0)//【要离开此状态】
	{	
		//可以黑屏下，做个切换动画
		cout<<"leave main_ui"<<endl;
	}
	else  //【要进入此状态,并开始执行此状态下的控制代码】
	{	
		cout<<"to main_ui"<<endl;
		//画主面板，并可以根据鼠标选择去向
		cout<<"--------------------"<<endl
		    <<"1.开始游戏"<<endl
			<<"2.选项"<<endl
		    <<"3.退出"<<endl
		    <<"--------------------"<<endl;
		char control=NULL;
		while(1)
		{
			control=NULL;
			while(kbhit()){control=getch();}
			switch(control)
			{
				case '1':
					changeGameProcessTo(START_COMBAT);
					changeGameProcessTo(COMBAT);
					changeGameProcessTo(MAIN_UI);   //有这句话还是不对！ 不应该嵌套！
					break;
				case '2':
					changeGameProcessTo(OPTION);
					changeGameProcessTo(MAIN_UI);
					break;
				case '3':changeGameProcessTo(EXIT);break;
				default:break;
			}
		}
	}
}

void CgameProcessor::start_combat_controller(int to1_leave0)
{
	if(to1_leave0==0)//【要离开此状态】
	{
		cout<<"leave start combat"<<endl;
	}
	else  //【要进入此状态,并开始执行此状态下的控制代码】
	{	
		cout<<"to start combat"<<endl;
		changeGameProcessTo(LOADING); 
	}
}

void CgameProcessor::combat_controller(int to1_leave0)
{
	if(to1_leave0==0)//【要离开此状态】
	{
		cout<<"leave combat"<<endl;												 //【Question】这里需要检测么？ 对不同跳转做不同反应？
	}
	else  //【要进入此状态,并开始执行此状态下的控制代码】
	{	
		cout<<"to combat"<<endl;

		int r;
        ifstream readInformation("userConfig\\userConfig.txt",ios::binary);
		char c=readInformation.get();
        sscanf(&c, "%d", &r);
		PLAYERNUM=r;
		srand( (unsigned)time( NULL ) );  //设置随机种子
		CcombatData combatData;
		CcombatShower combatShower;

		cout<<"开始战斗吧,骚年！"<<endl;
		system("pause");

		//初始化
		combatData.initData(combatData);
		combatShower.open(combatData);
		combatShower.show(combatData);
		combatData.battleField.putTankToUpSurface(combatData,combatShower);
		//开始循环
		combatData.dataRun(combatData,combatShower);
	
		combatShower.close();
		system("pause");
	}
}


void CgameProcessor::combat_break_controller(int to1_leave0)
{
	;
}


void CgameProcessor::exit_controller(int to1_leave0)
{
	if(to1_leave0==0)//【要离开此状态】
	{
	}
	else  //【要进入此状态,并开始执行此状态下的控制代码】
	{	
		cout<<"to exit"<<endl;
		//画个退出动画
		exit(0);
	}
}

void CgameProcessor::option_controller(int to1_leave0)
{
	if(to1_leave0==0)//【要离开此状态】
	{
		cout<<"leave option"<<endl;		
	}
	else  //【要进入此状态,并开始执行此状态下的控制代码】
	{	
		cout<<"to option"<<endl;
		cout<<"option changing..."<<endl;
lable_inputbox:   
		char s[10],s1[10];
          
        if(InputBox(s/*接受指向字符串的指针*/, 50,"您要几个人一起玩呢(1~4)","选择玩家数"/*窗体句柄位置所显示的东西*/,"2"/*用于设置默任输入值*/,100,100,false))//可以用来定义窗口的大小
		{   
			int r;
		    sscanf(s, "%d", &r);
			ofstream gotInformation("userConfig\\userConfig.txt",ios::binary);
            gotInformation<<r;
			//if(gotInformation)cout<<"文件成功复制";
            gotInformation.close();
		}

		if(InputBox(s1/*接受指向字符串的指针*/, 50,"请输入地图编号(0~9),按Ctrl+Enter确定","游戏地图选择"/*窗体句柄位置所显示的东西*/,"0"/*用于设置默任输入值*/,100,100,false))//可以用来定义窗口的大小
		{
			// 将用户输入转换为数字
			int r1;
			sscanf(s1, "%d", &r1);
			if(r1>=MAP_MAX_NUM){cout<<"Error!输入数值超过系统设定的地图最大张数了！按任意键退出程序...";getch();exit(0);}

			//copy背景
			{
				ofstream gotPicture("res\\map\\cntMap\\background.bmp",ios::binary);
				ifstream *sourceFile=new ifstream[MAP_MAX_NUM];
				sourceFile[0].open("res\\map\\map0\\background.bmp",ios::binary);
				sourceFile[1].open("res\\map\\map1\\background.bmp",ios::binary);
				sourceFile[2].open("res\\map\\map2\\background.bmp",ios::binary);
				sourceFile[3].open("res\\map\\map3\\background.bmp",ios::binary);
				sourceFile[4].open("res\\map\\map4\\background.bmp",ios::binary);
				sourceFile[5].open("res\\map\\map5\\background.bmp",ios::binary);
				sourceFile[6].open("res\\map\\map6\\background.bmp",ios::binary);
				sourceFile[7].open("res\\map\\map7\\background.bmp",ios::binary);
				sourceFile[8].open("res\\map\\map8\\background.bmp",ios::binary);
				sourceFile[9].open("res\\map\\map9\\background.bmp",ios::binary);  //没有的文件，就打不开了。【这里要做下处理机制！】
				if(!sourceFile[r1])//【【增加了判断文件是否能打开的机制
			   {
				   cout<<"该文件不存在或已被删除,请重新选择";
				   goto lable_inputbox;
			   }
				else  
				{
				while(!sourceFile[r1].eof())
				{
					gotPicture.put(sourceFile[r1].get());
				}
				gotPicture.close();
				for(int i=0;i<MAP_MAX_NUM;i++)
				{
					sourceFile[i].close();
				}
			   }
				delete []sourceFile;
			}
			//copy地面
			{
				ofstream gotPicture("res\\map\\cntMap\\earth.bmp",ios::binary);
				ifstream *sourceFile=new ifstream[MAP_MAX_NUM];
				sourceFile[0].open("res\\map\\map0\\earth.bmp",ios::binary);
				sourceFile[1].open("res\\map\\map1\\earth.bmp",ios::binary);
				sourceFile[2].open("res\\map\\map2\\earth.bmp",ios::binary);
				sourceFile[3].open("res\\map\\map3\\earth.bmp",ios::binary);
				sourceFile[4].open("res\\map\\map4\\earth.bmp",ios::binary);
				sourceFile[5].open("res\\map\\map5\\earth.bmp",ios::binary);
				sourceFile[6].open("res\\map\\map6\\earth.bmp",ios::binary);
				sourceFile[7].open("res\\map\\map7\\earth.bmp",ios::binary);
				sourceFile[8].open("res\\map\\map8\\earth.bmp",ios::binary);
				sourceFile[9].open("res\\map\\map9\\earth.bmp",ios::binary);  //没有的文件，就打不开了。【这里要做下处理机制！】
 
			
				if(!sourceFile[r1])//【【增加了判断文件是否能打开的机制
				{
					cout<<"该文件不存在或已被删除,请重新选择";
					goto lable_inputbox;
				}
				else
				{
					while(!sourceFile[r1].eof())
					{
						gotPicture.put(sourceFile[r1].get());
					}
					gotPicture.close();
					for(int i=0;i<MAP_MAX_NUM;i++)
					{
						sourceFile[i].close();
					}
				}
				delete []sourceFile;
			}
			//copy音乐
			{
				ofstream gotPicture("res\\map\\cntMap\\backgroundMusic.mp3",ios::binary);
				ifstream *sourceFile=new ifstream[MAP_MAX_NUM];
				sourceFile[0].open("res\\map\\map0\\backgroundMusic.mp3",ios::binary);
				sourceFile[1].open("res\\map\\map1\\backgroundMusic.mp3",ios::binary);
				sourceFile[2].open("res\\map\\map2\\backgroundMusic.mp3",ios::binary);
				sourceFile[3].open("res\\map\\map3\\backgroundMusic.mp3",ios::binary);
				sourceFile[4].open("res\\map\\map4\\backgroundMusic.mp3",ios::binary);
				sourceFile[5].open("res\\map\\map5\\backgroundMusic.mp3",ios::binary);
				sourceFile[6].open("res\\map\\map6\\backgroundMusic.mp3",ios::binary);
				sourceFile[7].open("res\\map\\map7\\backgroundMusic.mp3",ios::binary);
				sourceFile[8].open("res\\map\\map8\\backgroundMusic.mp3",ios::binary);
				sourceFile[9].open("res\\map\\map9\\backgroundMusic.mp3",ios::binary);  //没有的文件，就打不开了。【这里要做下处理机制！】
				if(!sourceFile[r1])
				{
					cout<<"该文件不存在或已被删除,请重新选择";
					goto lable_inputbox;
				}
				else
				{
					while(!sourceFile[r1].eof())
					{
						gotPicture.put(sourceFile[r1].get());
					}
					gotPicture.close();
					for(int i=0;i<MAP_MAX_NUM;i++)
					{
						sourceFile[i].close();
					}
				}
				delete []sourceFile;
			}
		}
	}
}

/*
不能让它一层层深入而出不来！
要有回跳机制
*/







