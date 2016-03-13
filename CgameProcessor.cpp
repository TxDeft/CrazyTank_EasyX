//����������Qusetion������������tank hp�ĳ� int �ƺ������⡭��Ϊë�ử����ô����Ѫ������   ��ͼ�ط� int���У�

//������Ϸ����ȡ�������棺{��ʼ��Ϸ��ѡ��и�ѡ���Ƿ�¼�񣩣��طţ���Ϸ˵�����������ǣ��˳�}
//��Ϸ�У�BREAK {��Ϸ˵�������������棬���¿�ʼ���˳���Ϸ}

//CgameProcessor.cpp
//include �� ǰ����������.......................................................................
#include "common.h"
#include"CgameProcessor.h"
using namespace std;
extern int PLAYERNUM;

//..............................................................................................

CgameProcessor::CgameProcessor()
{
	for(int i=0;i<MAX_PROCESS_NUM;i++)
	{
		gameProcesses[i]=NOPROCESS;   //0���ʼ��NOPROCESSԤ��ģ����ڵ�һ���뿪���� 0-9���Ǻ��ڿ��õ�PROCESS��
	}
	cntProcessStep=0;
}

void CgameProcessor::changeGameProcessTo(enum GameProcess newGP)          //��������ȷ��cntָ�����Ѿ���ӽ�ȥ�ĵĵ�ǰλ�á���û��ȫ�˳��Ĳ��㡣�Ѿ���ȥ����
{
	int p=findExistProcess(newGP);
	if(p!=-1) //�������Ѵ��ڵ����̴���
	{
		for(int i=cntProcessStep;i>p;i--)   //�˻ص��ظ�λ��
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
				//����
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
			//����
			default:break;
		}
	}

	else //�����һ��û�е������̡�
	{
		//1.�뿪�;�����
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
			//����
			default:break;
		}
		//2.����������
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
			//����
			default:break;
		}
	}	
}

int CgameProcessor::findExistProcess(enum GameProcess GP)   //����һ�������������������±ꡣ  �޵�ʱ�򷵻�-1��
{
	for(int i=0;i<=cntProcessStep;i++)
	{
		if(gameProcesses[i]==GP){return i;}
	}
	return -1;
}


void CgameProcessor::loading_controller(int to1_leave0)
{
	if(to1_leave0==0)//��Ҫ�뿪��״̬��
	{
		//���������Լ�����ϣ��������������
		cout<<"finish loading,press any button to continue"<<endl;
		getch();
		cout<<"leave loading"<<endl;
	}
	else  //��Ҫ�����״̬,����ʼִ�д�״̬�µĿ��ƴ��롿
	{	
		cout<<"to loading"<<endl;
		//����loading�Ļ�
		cout<<"now loading..."<<endl;
		Sleep(1000);//��������- -
	}
}

void CgameProcessor::main_ui_controller(int to1_leave0)
{
	if(to1_leave0==0)//��Ҫ�뿪��״̬��
	{	
		//���Ժ����£������л�����
		cout<<"leave main_ui"<<endl;
	}
	else  //��Ҫ�����״̬,����ʼִ�д�״̬�µĿ��ƴ��롿
	{	
		cout<<"to main_ui"<<endl;
		//������壬�����Ը������ѡ��ȥ��
		cout<<"--------------------"<<endl
		    <<"1.��ʼ��Ϸ"<<endl
			<<"2.ѡ��"<<endl
		    <<"3.�˳�"<<endl
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
					changeGameProcessTo(MAIN_UI);   //����仰���ǲ��ԣ� ��Ӧ��Ƕ�ף�
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
	if(to1_leave0==0)//��Ҫ�뿪��״̬��
	{
		cout<<"leave start combat"<<endl;
	}
	else  //��Ҫ�����״̬,����ʼִ�д�״̬�µĿ��ƴ��롿
	{	
		cout<<"to start combat"<<endl;
		changeGameProcessTo(LOADING); 
	}
}

void CgameProcessor::combat_controller(int to1_leave0)
{
	if(to1_leave0==0)//��Ҫ�뿪��״̬��
	{
		cout<<"leave combat"<<endl;												 //��Question��������Ҫ���ô�� �Բ�ͬ��ת����ͬ��Ӧ��
	}
	else  //��Ҫ�����״̬,����ʼִ�д�״̬�µĿ��ƴ��롿
	{	
		cout<<"to combat"<<endl;

		int r;
        ifstream readInformation("userConfig\\userConfig.txt",ios::binary);
		char c=readInformation.get();
        sscanf(&c, "%d", &r);
		PLAYERNUM=r;
		srand( (unsigned)time( NULL ) );  //�����������
		CcombatData combatData;
		CcombatShower combatShower;

		cout<<"��ʼս����,ɧ�꣡"<<endl;
		system("pause");

		//��ʼ��
		combatData.initData(combatData);
		combatShower.open(combatData);
		combatShower.show(combatData);
		combatData.battleField.putTankToUpSurface(combatData,combatShower);
		//��ʼѭ��
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
	if(to1_leave0==0)//��Ҫ�뿪��״̬��
	{
	}
	else  //��Ҫ�����״̬,����ʼִ�д�״̬�µĿ��ƴ��롿
	{	
		cout<<"to exit"<<endl;
		//�����˳�����
		exit(0);
	}
}

void CgameProcessor::option_controller(int to1_leave0)
{
	if(to1_leave0==0)//��Ҫ�뿪��״̬��
	{
		cout<<"leave option"<<endl;		
	}
	else  //��Ҫ�����״̬,����ʼִ�д�״̬�µĿ��ƴ��롿
	{	
		cout<<"to option"<<endl;
		cout<<"option changing..."<<endl;
lable_inputbox:   
		char s[10],s1[10];
          
        if(InputBox(s/*����ָ���ַ�����ָ��*/, 50,"��Ҫ������һ������(1~4)","ѡ�������"/*������λ������ʾ�Ķ���*/,"2"/*��������Ĭ������ֵ*/,100,100,false))//�����������崰�ڵĴ�С
		{   
			int r;
		    sscanf(s, "%d", &r);
			ofstream gotInformation("userConfig\\userConfig.txt",ios::binary);
            gotInformation<<r;
			//if(gotInformation)cout<<"�ļ��ɹ�����";
            gotInformation.close();
		}

		if(InputBox(s1/*����ָ���ַ�����ָ��*/, 50,"�������ͼ���(0~9),��Ctrl+Enterȷ��","��Ϸ��ͼѡ��"/*������λ������ʾ�Ķ���*/,"0"/*��������Ĭ������ֵ*/,100,100,false))//�����������崰�ڵĴ�С
		{
			// ���û�����ת��Ϊ����
			int r1;
			sscanf(s1, "%d", &r1);
			if(r1>=MAP_MAX_NUM){cout<<"Error!������ֵ����ϵͳ�趨�ĵ�ͼ��������ˣ���������˳�����...";getch();exit(0);}

			//copy����
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
				sourceFile[9].open("res\\map\\map9\\background.bmp",ios::binary);  //û�е��ļ����ʹ򲻿��ˡ�������Ҫ���´�����ƣ���
				if(!sourceFile[r1])//�����������ж��ļ��Ƿ��ܴ򿪵Ļ���
			   {
				   cout<<"���ļ������ڻ��ѱ�ɾ��,������ѡ��";
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
			//copy����
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
				sourceFile[9].open("res\\map\\map9\\earth.bmp",ios::binary);  //û�е��ļ����ʹ򲻿��ˡ�������Ҫ���´�����ƣ���
 
			
				if(!sourceFile[r1])//�����������ж��ļ��Ƿ��ܴ򿪵Ļ���
				{
					cout<<"���ļ������ڻ��ѱ�ɾ��,������ѡ��";
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
			//copy����
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
				sourceFile[9].open("res\\map\\map9\\backgroundMusic.mp3",ios::binary);  //û�е��ļ����ʹ򲻿��ˡ�������Ҫ���´�����ƣ���
				if(!sourceFile[r1])
				{
					cout<<"���ļ������ڻ��ѱ�ɾ��,������ѡ��";
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
��������һ����������������
Ҫ�л�������
*/







