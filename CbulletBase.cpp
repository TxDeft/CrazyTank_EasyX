//CbulletBase.cpp
//include 和 前向引用声明.......................................................................
#include "common.h"
#include"CbulletBase.h"
using namespace std;

extern int PLAYERNUM;

//..............................................................................................


CbulletBase::CbulletBase()
{  
	v0=0;
	exist=0;
	bombOrNot=0;
	bWidth=BULLETWIDTH;
	bHeight=BULLETHEIGHT;
	bulletName=BULLETBASE;
}

void CbulletBase::createBullet(CcombatData & combatData)
{ 
	v0=(combatData.tank[combatData.whoIsPlaying].launchStrength)*(STRENGTH_TO_V0);  //比例关系调试时调整
	exist=1;
	//position.x=combatData.tank[combatData.whoIsPlaying].position.x;
	//position.y=combatData.tank[combatData.whoIsPlaying].position.y+TANKHEIGHT;
	double modifyH=0.6,modifyW=1.1;


	if(combatData.tank[combatData.whoIsPlaying].tankDirection==1)
	{
	   position.x=combatData.tank[combatData.whoIsPlaying].position.x-modifyH*TANKHEIGHT*sin(combatData.tank[combatData.whoIsPlaying].tankCita)+combatData.tank[combatData.whoIsPlaying].tankDirection*0.5*modifyW*TANKWIDTH*cos(combatData.tank[combatData.whoIsPlaying].tankCita);
 
       position.y=combatData.tank[combatData.whoIsPlaying].position.y+modifyH*TANKHEIGHT*cos(combatData.tank[combatData.whoIsPlaying].tankCita)+combatData.tank[combatData.whoIsPlaying].tankDirection*0.5*modifyW*TANKWIDTH*sin(combatData.tank[combatData.whoIsPlaying].tankCita);
	}
	else
	{
		position.x=combatData.tank[combatData.whoIsPlaying].position.x-0.5*modifyW*TANKWIDTH*cos(combatData.tank[combatData.whoIsPlaying].tankCita)+sin(combatData.tank[combatData.whoIsPlaying].tankCita)*modifyH*TANKHEIGHT;
		position.y=combatData.tank[combatData.whoIsPlaying].position.y+0.5*modifyW*TANKWIDTH*sin(combatData.tank[combatData.whoIsPlaying].tankCita)+cos(combatData.tank[combatData.whoIsPlaying].tankCita)*modifyH*TANKHEIGHT;
	}
}

void CbulletBase::eliminateBullet()
{
	exist=0;
}



//……………………………………………………此函数控制子弹的移动轨迹，需要改变子弹的位置……………………………………………………
void CbulletBase::fly(CcombatData & combatData,CcombatShower & combatShower)
{ 
	Cpoint bombP;
	double t;//时间
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//计算出炮弹相对于地面的发射角

	//【在发射的一瞬间就预判出爆炸点】——防炸的一瞬间卡
	//bombP.reset(0,0);
	//for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//用于改变子弹的位置
	//{
	//	if(judgeCollision((int)position.x,(int)position.y,combatData))
	//	{
	//		bombP.reset(position.x,position.y);
	//		break;
	//	}
	//}

	//【以下用于整个过程的放映】
	position.x=x0;
	position.x=y0;;
	//combatShower.show(combatData);
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//用于改变子弹的位置
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//清除 只改变exsit的值，其它都不要碰
			combatShower.show(combatData);
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			bombOrNot=0;
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//调用画图函数
		//Sleep(SLEEP_TIME);
	}
	eliminateBullet();  //直接飞出去的，也清除子弹
}



//……………………………………………………子弹的爆炸函数，将地图信息与子弹的位置结合起来了………………
void CbulletBase::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	//以下这段是防止炸弹在地图边缘的时候，有数组溢出的危险
	int modify=5;//检测范围扩大一下
	int xLeft=(int)((position.x-BOMBR-modify<0)? 0:(position.x-BOMBR-modify));
	int xRight=(int)((position.x+BOMBR+modify>BFWIDTH-1)? (BFWIDTH-1):(position.x+BOMBR+modify));
	int yBottom=(int)((position.y-BOMBR-modify<0)? 0:(position.y-BOMBR-modify));
	int yHead=(int)((position.y+BOMBR+modify>BFHEIGHT-1)? (BFHEIGHT-1):(position.y+BOMBR+modify));

	//以下代码用来计算子弹应该爆炸的范围,将受爆炸影响的map数组值赋值为0
	combatData.battleField.startChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);
	for(int x=xLeft;x<=xRight;x++)//条件用于控制
	{
		for(int y=yBottom;y<=yHead;y++)
		{
			  if(combatData.battleField.map[x][y]!=0)    //判断子弹爆炸的位置是否是在地形处       
			  {
				  if((int)(position.dist(Cpoint(x,y),position)+0.5)<=BOMBR)
				  {  
					 combatData.battleField.changeMapValueTo(x,y,0);
				  }		  
			  }
		}
	}
	combatData.battleField.finishChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);

	//以下程序用于检验坦克是否在子弹爆炸范围内，需要改变血量的值
	for(int i=0;i<PLAYERNUM;i++)
	{
		if(combatData.tank[i].hp>0)
		{
			double d=position.dist(position,combatData.tank[i].position);
			if(d<=BOMBR)
			{
				combatData.tank[i].changeHpTo((int)(combatData.tank[i].hp-BOMB_MAX_DAMAGE*(1-d*1.0/BOMBR)),combatData,combatShower);
			}
		}
	}
	//cout<<"子弹已经爆炸"<<endl;
}

int CbulletBase::changePositionTo(double newx,double newy)   //子弹的坐标是自由的，因为不涉及map数组溢出
{
	if(newx<0 || newx>=BFWIDTH || newy<0)  //y不设上限，这样飞到天上可以回来
	{
		eliminateBullet();return 0;
	}
	else
	{
		position.reset(newx,newy);return 1;
	}
}



bool CbulletBase::judgeCollision(int x,int y,CcombatData & combatData)
{
	//主要检测和地面的碰撞，有碰撞体积
	int xLeft=(int)((x-BULLET_COLLISION_R<0)? 0:(x-BULLET_COLLISION_R));
	int xRight=(int)((x+BULLET_COLLISION_R>BFWIDTH)? BFWIDTH:(x+BULLET_COLLISION_R));
	int yBottom=(int)((y-BULLET_COLLISION_R<0)? 0:(y-BULLET_COLLISION_R));
	int yHead=(int)((y+BULLET_COLLISION_R>BFHEIGHT)? BFHEIGHT:(y+BULLET_COLLISION_R));
	for(int x=xLeft;x<xRight;x++)
	{
		for(int y=yBottom;y<yHead;y++)
		{
			if(combatData.battleField.map[x][y]!=0)
			{
				return true;
			}
		}
	}

	//主要检测和tank的碰撞，都有碰撞体积
	for(int i=0;i<PLAYERNUM;i++)
	{
		if(combatData.tank[i].hp>0 && i!=combatData.whoIsPlaying) //不会炸自己
		{
			if(position.dist(position,combatData.tank[i].position)<=BULLET_COLLISION_R+TANK_COLLISION_R)
			{
				return true;
			}
		}
	}
	return false;
}
