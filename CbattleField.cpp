//CbattleField.cpp
//include 和 前向引用声明.......................................................................
#include "common.h"
#include"CbattleField.h"
using namespace std;



//..............................................................................................


//构造函数
CbattleField::CbattleField()
{
	bfWidth=BFWIDTH;//给背景宽度赋值
	bfHeight=BFHEIGHT;//给背景高度赋值
	map= new int[BFWIDTH][BFHEIGHT];//为解决栈溢出，实行动态分配内存
	mapChanging=false;
}


//析构函数
CbattleField::~CbattleField()
{   
	delete [] map;
    map=0;
	//cout<<"The BattleField Has been ruined"<<endl;
}


//地图初始化 
void CbattleField::initMap(CcombatData &combatData)
{

	//for(int i=0;i<BFWIDTH;i++)//初始化地形
	//{
	//	for(int j=0;j<BFHEIGHT;j++)
	//	{
	//       (map[i])[j]=0;
	//	}
	//}
 //   //memset(map,0,sizeof(map));//用于给一整块内存初始化 【没成功！妹的为毛啊】
 //   for(int i=0.15*BFWIDTH;i<(0.85*BFWIDTH);i++)//初始化地形
	//{
	//	for(int j=0;j<(0.3*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	// for(int i=0.12*BFWIDTH;i<(0.92*BFWIDTH);i++)//初始化地形
	//{
	//	for(int j=0;j<(0.2*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0;i<BFWIDTH;i++)//初始化地形
	//{
	//	for(int j=0;j<(0.1*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0.3*BFWIDTH;i<(0.4*BFWIDTH);i++)//初始化地形
	//{
	//	for(int j=0.4*BFHEIGHT;j<(0.8*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0.4*BFWIDTH;i<(0.45*BFWIDTH);i++)//初始化地形
	//{
	//	for(int j=0.4*BFHEIGHT;j<(0.7*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0.7*BFWIDTH;i<(0.8*BFWIDTH);i++)//初始化地形
	//{
	//	for(int j=0.3*BFHEIGHT;j<(0.35*BFHEIGHT);j++)
	//	{
	//       map[i][j]=1;
	//	}
	//}
	//for(int i=0.6*BFWIDTH;i<(0.82*BFWIDTH);i++)//初始化地形
	//{
	//	for(int j=0;j<(0.2*BFHEIGHT);j++)
	//	{
	//       map[i][j]=0;
	//	}
	//}
	//for(int i=0.15*BFWIDTH;i<(0.3*BFWIDTH);i++)//初始化地形
	//{
	//	for(int j=0;j<(0.25*BFHEIGHT);j++)
	//	{
	//       map[i][j]=0;
	//	}
	//}

	createMapFromPicture();
	changeUpSurface1to2(0,0,BFWIDTH-1,BFHEIGHT-1,combatData);
}


//【表示从x1到x2点；【【x1和x2都包括在内】】！！！】
//【左下坐标and右上坐标】
void CbattleField::changeUpSurface1to2(int x1,int y1,int x2,int y2,CcombatData &combatData) //把地图一矩形范围内所有位于上表面的1点的值转成2.方便识别查找上表面。
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


int CbattleField::getUpSurfaceY(Cpoint &eventP,CcombatData &combatData) //给一个点，返回在该点X的位置上附近的上表面的Y的坐标-即是2的点
{
	int surfaceY=0;
	if(eventP.x<0 || eventP.x>=BFWIDTH || eventP.y<0 || eventP.y>=BFHEIGHT)
	{
		cout<<"Error-2"<<endl;
		return 1000;
	}

	int ex=(int)eventP.x;  //点是double->数组下标只能是整数
	int ey=(int)eventP.y;
	if(map[ex][ey]==0)// ==0  说明是悬空了 。需要向下检索  
	{
		int y;
		for(y=ey;y>=0;y--)
		{
			if(map[ex][y]!=0){break;}   //【收获！】break后，不再执行for的第三语句了
		}
		surfaceY=y;
	}
	else //说明在土里了
	{
		int y;
		for(y=ey;y<BFHEIGHT;y++)
		{
			if(map[ex][y]==0){surfaceY=y-1;return surfaceY;}   //【收获！】break后，不再执行for的第三语句了
		}
		surfaceY=y;
	}
	return surfaceY;
}

double CbattleField::getUpSurfaceCita(Cpoint &p,CcombatData &combatData)//给一个点，返回在该点的切线角（正负PI/2）。前提是确保该点的map值是2，是上表面！
{
	/*
	计算角的之前，要保证这个点是2点
	算的是与x+的cita夹角  （正负PI/2）
	算该点左右各加减0.5*TANKWIDTH的x范围内，计算每相邻两点间的斜率，并算平均值。并转为cita
	*/
	int xi=(int)p.x;
	int yi=(int)p.y;
	if(map[xi][yi]!=2){cout<<"Error-3"<<endl;return 1314+2.4;}          //其实这些【数字的含义】，也都可以用宏定义定的~。~

	double r=1.5*DMOVE;  //扫描半径
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
			/*importance=(x-p.x)/(r*r)+1.0/r;*///权重直线下降版
			importance=a*dx*dx-b*dx+c;//权重二次函数下降版
		}
		else
		{
			/*importance=-(x-p.x)/(r*r)+1.0/r;*/
			importance=a*dx*dx+b*dx+c;
		}
		sumK+=k[kNum]*importance;
	}
	double kAverage=sumK;
	return atan(kAverage);   //（正负PI/2）之间
}

void CbattleField::putTankToUpSurface(CcombatData &combatData,CcombatShower & combatShower)//这个函数在这里比较好。因为一次爆炸肯能引起多个tank下降。这样处理所有tank即可
{
	/*
	这个函数在tank主动移动or有任何map改变（如爆炸）后调用。
																				不做这个检测了也行：检测，如果bombOrNot=0；则是前者，bombOrNot=1；则是后者
	直接暴力遍历所有tank的坐标，看该坐标的map是不是2
	如果不是，计算在那个位置上的
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
//…………………………此处为改变地图值的函数……
int  CbattleField::changeMapValueTo(int x,int y,int newValue)
{   
	  map[x][y]=newValue;
	  return 0;

}

int  CbattleField::startChangeMapValue(double xl,double yb,double xr,double yh,CcombatData &combatData)//开始改变地形时
{           
	mapChanging=true;//地形开始改变
	return 0; 
}
	
int  CbattleField::finishChangeMapValue(double xl,double yb,double xr,double yh,CcombatData &combatData)
{  
	mapChanging=false;//地图停止改变
	changeUpSurface1to2((int)xl,(int)yb,(int)xr,(int)yh,combatData);

	return 0;
}


void CbattleField::createMapFromPicture()
{
	IMAGE img;
	loadimage(&img,"res\\map\\cntMap\\earth.bmp",BFWIDTH,BFHEIGHT);
	DWORD* p=GetImageBuffer(&img);
	for(int j=0;j<(BFHEIGHT);j++)//初始化地形
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
