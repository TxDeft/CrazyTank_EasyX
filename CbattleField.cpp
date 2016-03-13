//CbattleField.cpp
//include �� ǰ����������.......................................................................
#include "common.h"
#include"CbattleField.h"
using namespace std;



//..............................................................................................


//���캯��
CbattleField::CbattleField()
{
	bfWidth=BFWIDTH;//��������ȸ�ֵ
	bfHeight=BFHEIGHT;//�������߶ȸ�ֵ
	map= new int[BFWIDTH][BFHEIGHT];//Ϊ���ջ�����ʵ�ж�̬�����ڴ�
	mapChanging=false;
}


//��������
CbattleField::~CbattleField()
{   
	delete [] map;
    map=0;
	//cout<<"The BattleField Has been ruined"<<endl;
}


//��ͼ��ʼ�� 
void CbattleField::initMap(CcombatData &combatData)
{

	//for(int i=0;i<BFWIDTH;i++)//��ʼ������
	//{
	//	for(int j=0;j<BFHEIGHT;j++)
	//	{
	//       (map[i])[j]=0;
	//	}
	//}
 //   //memset(map,0,sizeof(map));//���ڸ�һ�����ڴ��ʼ�� ��û�ɹ����õ�Ϊë����
 //   for(int i=0.15*BFWIDTH;i<(0.85*BFWIDTH);i++)//��ʼ������
	//{
	//	for(int j=0;j<(0.3*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	// for(int i=0.12*BFWIDTH;i<(0.92*BFWIDTH);i++)//��ʼ������
	//{
	//	for(int j=0;j<(0.2*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0;i<BFWIDTH;i++)//��ʼ������
	//{
	//	for(int j=0;j<(0.1*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0.3*BFWIDTH;i<(0.4*BFWIDTH);i++)//��ʼ������
	//{
	//	for(int j=0.4*BFHEIGHT;j<(0.8*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0.4*BFWIDTH;i<(0.45*BFWIDTH);i++)//��ʼ������
	//{
	//	for(int j=0.4*BFHEIGHT;j<(0.7*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0.7*BFWIDTH;i<(0.8*BFWIDTH);i++)//��ʼ������
	//{
	//	for(int j=0.3*BFHEIGHT;j<(0.35*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0.6*BFWIDTH;i<(0.82*BFWIDTH);i++)//��ʼ������
	//{
	//	for(int j=0;j<(0.2*BFHEIGHT);j++)
	//	{
	//       map[i][j]=0;
	//	}
	//}
	//for(int i=0.15*BFWIDTH;i<(0.3*BFWIDTH);i++)//��ʼ������
	//{
	//	for(int j=0;j<(0.25*BFHEIGHT);j++)
	//	{
	//       map[i][j]=0;
	//	}
	//}

	createMapFromPicture();
	changeUpSurface1to2(0,0,BFWIDTH-1,BFHEIGHT-1,combatData);
}


//����ʾ��x1��x2�㣻����x1��x2���������ڡ�����������
//����������and�������꡿
void CbattleField::changeUpSurface1to2(int x1,int y1,int x2,int y2,CcombatData &combatData) //�ѵ�ͼһ���η�Χ������λ���ϱ����1���ֵת��2.����ʶ������ϱ��档
{
	/*x1=(x1<0)? 0:x1;
	x2=(x2>BFWIDTH)? BFWIDTH:x2;
	y1=(y1<0)? 0:y1;
	y2=(y2>BFHEIGHT)? BFHEIGHT:y2;*/
	if(x1<0 || x2>BFWIDTH-1 || y1<0 || y2>BFHEIGHT-1)
	{
		cout<<"Error-1"<<endl;
		return;
	}

	for(int x=x1;x<=x2;x++)
	{
		for(int y=y1;y<=y2;y++)
		{
			if(map[x][y]==0)
			{
				if(y>0 && map[x][y-1]==1)
				{
					map[x][y-1]=2;
				}
			}
		}
	}
}


int CbattleField::getUpSurfaceY(Cpoint &eventP,CcombatData &combatData) //��һ���㣬�����ڸõ�X��λ���ϸ������ϱ����Y������-����2�ĵ�
{
	int surfaceY=0;
	if(eventP.x<0 || eventP.x>=BFWIDTH || eventP.y<0 || eventP.y>=BFHEIGHT)
	{
		cout<<"Error-2"<<endl;
		return 1000;
	}

	int ex=(int)eventP.x;  //����double->�����±�ֻ��������
	int ey=(int)eventP.y;
	if(map[ex][ey]==0)// ==0  ˵���������� ����Ҫ���¼���  
	{
		int y;
		for(y=ey;y>=0;y--)
		{
			if(map[ex][y]!=0){break;}   //���ջ񣡡�break�󣬲���ִ��for�ĵ��������
		}
		surfaceY=y;
	}
	else //˵����������
	{
		int y;
		for(y=ey;y<BFHEIGHT;y++)
		{
			if(map[ex][y]==0){surfaceY=y-1;return surfaceY;}   //���ջ񣡡�break�󣬲���ִ��for�ĵ��������
		}
		surfaceY=y;
	}
	return surfaceY;
}

double CbattleField::getUpSurfaceCita(Cpoint &p,CcombatData &combatData)//��һ���㣬�����ڸõ�����߽ǣ�����PI/2����ǰ����ȷ���õ��mapֵ��2�����ϱ��棡
{
	/*
	����ǵ�֮ǰ��Ҫ��֤�������2��
	�������x+��cita�н�  ������PI/2��
	��õ����Ҹ��Ӽ�0.5*TANKWIDTH��x��Χ�ڣ�����ÿ����������б�ʣ�����ƽ��ֵ����תΪcita
	*/
	int xi=(int)p.x;
	int yi=(int)p.y;
	if(map[xi][yi]!=2){cout<<"Error-3"<<endl;return 1314+2.4;}          //��ʵ��Щ�����ֵĺ��塿��Ҳ�������ú궨�嶨��~��~

	double r=1.5*DMOVE;  //ɨ��뾶
	double surfaceCita=0.0;
	int xl=(int)(p.x-r);
	int xr=(int)(p.x+r);
	xl=(xl<0)? 0:xl;
	xr=(xr>BFWIDTH)? BFWIDTH:xr;
	
	double k[TANKWIDTH+2],sumK=0.0;
	int kNum,x,y1,y2;
	for(x=xl,kNum=0;x<xr;x++,kNum++)
	{
		y1=getUpSurfaceY(Cpoint(x,p.y),combatData);
		y2=getUpSurfaceY(Cpoint(x+1,p.y),combatData);
		k[kNum]=(y2-y1)/1.0;
		double importance;
		double dx=x-p.x;
		double a=1.5/(r*r*r),b=-3/(r*r),c=1.5/r;
		if(dx<0)
		{
			/*importance=(x-p.x)/(r*r)+1.0/r;*///Ȩ��ֱ���½���
			importance=a*dx*dx-b*dx+c;//Ȩ�ض��κ����½���
		}
		else
		{
			/*importance=-(x-p.x)/(r*r)+1.0/r;*/
			importance=a*dx*dx+b*dx+c;
		}
		sumK+=k[kNum]*importance;
	}
	double kAverage=sumK;
	return atan(kAverage);   //������PI/2��֮��
}

void CbattleField::putTankToUpSurface(CcombatData &combatData,CcombatShower & combatShower)//�������������ȽϺá���Ϊһ�α�ը����������tank�½���������������tank����
{
	/*
	���������tank�����ƶ�or���κ�map�ı䣨�籬ը������á�
																				������������Ҳ�У���⣬���bombOrNot=0������ǰ�ߣ�bombOrNot=1�����Ǻ���
	ֱ�ӱ�����������tank�����꣬���������map�ǲ���2
	������ǣ��������Ǹ�λ���ϵ�
	*/
	for(int i=0;i<combatData.playerNum;i++)
	{
		if(combatData.tank[i].position.y>=0)
		{
			int tkx=(int)combatData.tank[i].position.x;
			int tky=(int)combatData.tank[i].position.y;
			int newSurfaceY=0;;
			bool willDie=0;
			if(map[tkx][tky]!=2)
			{
				newSurfaceY=getUpSurfaceY(combatData.tank[i].position,combatData);
				if(newSurfaceY<0)
				{
					willDie=true;
				}
				for(;combatData.tank[i].position.y>newSurfaceY+DMOVE;combatData.tank[i].position.y-=DMOVE)
				{
					combatShower.show(combatData);
				}
				combatData.tank[i].position.y=newSurfaceY;
				double c=getUpSurfaceCita(combatData.tank[i].position,combatData);
				if(combatData.tank[i].hp>0)
				{
					combatData.tank[i].tankCita=(combatData.tank[i].tankDirection==1)? c:(-c);
				}
				else
				{
					combatData.tank[i].tankCita=-combatData.tank[i].tankCita;
				}
				combatShower.show(combatData);
				if(willDie){combatData.tank[i].changeHpTo(0,combatData,combatShower);}
			}
		}
	}
}
//���������������������˴�Ϊ�ı��ͼֵ�ĺ�������
int  CbattleField::changeMapValueTo(int x,int y,int newValue)
{   
	  map[x][y]=newValue;
	  return 0;

}

int  CbattleField::startChangeMapValue(double xl,double yb,double xr,double yh,CcombatData &combatData)//��ʼ�ı����ʱ
{           
	mapChanging=true;//���ο�ʼ�ı�
	return 0; 
}
	
int  CbattleField::finishChangeMapValue(double xl,double yb,double xr,double yh,CcombatData &combatData)
{  
	mapChanging=false;//��ͼֹͣ�ı�
	changeUpSurface1to2((int)xl,(int)yb,(int)xr,(int)yh,combatData);

	return 0;
}


void CbattleField::createMapFromPicture()
{
	IMAGE img;
	loadimage(&img,"res\\map\\cntMap\\earth.bmp",BFWIDTH,BFHEIGHT);
	DWORD* p=GetImageBuffer(&img);
	for(int j=0;j<(BFHEIGHT);j++)//��ʼ������
	{
		for(int i=0;i<(BFWIDTH);i++)
		{
			int index=i+j*BFWIDTH;
			if(GetBValue(p[index])==255 && GetGValue(p[index] )==255 && GetRValue(p[index])==255)
			{
				map[i][j]=0;
			}
			else
			{
				map[i][j]=1;
			}
		}
	}
}
