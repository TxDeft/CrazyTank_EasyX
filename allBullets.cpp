//allBullets.cpp
//include 和 前向引用声明.......................................................................
#include "common.h"
#include"allBullets.h"
using namespace std;

//..............................................................................................
 extern int PLAYERNUM;


//【普通子弹】
CbulletNormal::CbulletNormal()
{  
	v0=0;
	exist=0;
	bombOrNot=0;
	bWidth=BULLETWIDTH;
	bHeight=BULLETHEIGHT;
	bulletName=BULLETNORMAL;
}
void CbulletNormal::fly(CcombatData & combatData,CcombatShower & combatShower)
{ 
	Cpoint bombP;
	double t;//时间
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//计算出炮弹相对于地面的发射角
	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//用于改变子弹的位置
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//清除 只改变exsit的值，其它都不要碰
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//调用画图函数
	}
	eliminateBullet();  //直接飞出去的，也清除子弹
}
void CbulletNormal::bomb(CcombatData &combatData,CcombatShower &combatShower)
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
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //游戏中最远的打击距离，主对角线
	for(int i=0;i<PLAYERNUM;i++)
	{
		if(combatData.tank[i].hp>0)
		{
			double launchDist=position.dist(combatData.tank[i].position,combatData.tank[combatData.whoIsPlaying].position);
			double cntDoubleRate=launchDist/maxDist+DOUBLE_DAMAGE_BASIC_RATE;
			int k=rand()%((int)(1.0/cntDoubleRate));  
			if(k==0){combatData.tank[i].gotDoubleDamage=true;}
			double d=position.dist(position,combatData.tank[i].position);
			if(d<=BOMBR)
			{
				int damageK=(combatData.tank[i].gotDoubleDamage==true)? 2:1;
				d=(d<BULLET_COLLISION_R+TANK_COLLISION_R)? (BULLET_COLLISION_R+TANK_COLLISION_R):d;
				combatData.tank[i].changeHpTo((int)(combatData.tank[i].hp-damageK*BOMB_MAX_DAMAGE*(1-d*1.0/BOMBR)),combatData,combatShower);
			}
			combatData.tank[i].gotDoubleDamage=false;
		}
	}
	//cout<<"子弹已经爆炸"<<endl;
}

//【瞬移子弹】
CbulletBlink::CbulletBlink()
{  
	v0=0;
	exist=0;
	bombOrNot=0;
	bWidth=BULLETWIDTH;
	bHeight=BULLETHEIGHT;
	bulletName=BULLETBLINK;
}
void CbulletBlink::fly(CcombatData & combatData,CcombatShower & combatShower)
{ 
	Cpoint bombP;
	double t;//时间
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//计算出炮弹相对于地面的发射角

	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//用于改变子弹的位置
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//清除 只改变exsit的值，其它都不要碰
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//调用画图函数
		//Sleep(SLEEP_TIME);
	}
	eliminateBullet();  //直接飞出去的，也清除子弹
}
void CbulletBlink::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	combatData.tank[combatData.whoIsPlaying].changePositionTo(position.x,position.y);
}

//【原子弹】
CbulletNuclear::CbulletNuclear()
{  
	v0=0;
	exist=0;
	bombOrNot=0;
	bWidth=BULLETWIDTH;
	bHeight=BULLETHEIGHT;
	bulletName=BULLETNUCLEAR;
}
void CbulletNuclear::fly(CcombatData & combatData,CcombatShower & combatShower)
{ 
	Cpoint bombP;
	double t;//时间
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//计算出炮弹相对于地面的发射角

	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//用于改变子弹的位置
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//清除 只改变exsit的值，其它都不要碰
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//调用画图函数
		//Sleep(SLEEP_TIME);
	}
	eliminateBullet();  //直接飞出去的，也清除子弹
}
void CbulletNuclear::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	int rk=4; //【爆炸半径倍数】
	//以下这段是防止炸弹在地图边缘的时候，有数组溢出的危险
	int modify=5;//检测范围扩大一下
	int xLeft=(int)((position.x-BOMBR*rk-modify<0)? 0:(position.x-BOMBR*rk-modify));
	int xRight=(int)((position.x+BOMBR*rk+modify>BFWIDTH-1)? (BFWIDTH-1):(position.x+BOMBR*rk+modify));
	int yBottom=(int)((position.y-BOMBR*rk-modify<0)? 0:(position.y-BOMBR*rk-modify));
	int yHead=(int)((position.y+BOMBR*rk+modify>BFHEIGHT-1)? (BFHEIGHT-1):(position.y+BOMBR*rk+modify));

	//以下代码用来计算子弹应该爆炸的范围,将受爆炸影响的map数组值赋值为0
	combatData.battleField.startChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);
	for(int x=xLeft;x<=xRight;x++)//条件用于控制
	{
		for(int y=yBottom;y<=yHead;y++)
		{
			  if(combatData.battleField.map[x][y]!=0)    //判断子弹爆炸的位置是否是在地形处       
			  {
				  if((int)(position.dist(Cpoint(x,y),position)+0.5)<=BOMBR*rk)
				  {  
					 combatData.battleField.changeMapValueTo(x,y,0);
				  }		  
			  }
		}
	}
	combatData.battleField.finishChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);

	//以下程序用于检验坦克是否在子弹爆炸范围内，需要改变血量的值
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //游戏中最远的打击距离，主对角线
	for(int i=0;i<PLAYERNUM;i++)
	{
		if(combatData.tank[i].hp>0)
		{
			double launchDist=position.dist(combatData.tank[i].position,combatData.tank[combatData.whoIsPlaying].position);
			double cntDoubleRate=launchDist/maxDist+DOUBLE_DAMAGE_BASIC_RATE;
			int k=rand()%((int)(1.0/cntDoubleRate));  
			if(k==0){combatData.tank[i].gotDoubleDamage=true;}
			double d=position.dist(position,combatData.tank[i].position);
			if(d<=BOMBR*rk)
			{
				int damageK=(combatData.tank[i].gotDoubleDamage==true)? 2:1;
				d=(d<BULLET_COLLISION_R+TANK_COLLISION_R)? (BULLET_COLLISION_R+TANK_COLLISION_R):d;
				combatData.tank[i].changeHpTo((int)(combatData.tank[i].hp-damageK*BOMB_MAX_DAMAGE*(1-d*1.0/(BOMBR*rk))),combatData,combatShower);
			}
			combatData.tank[i].gotDoubleDamage=false;
		}
	}
	//cout<<"子弹已经爆炸"<<endl;
}

//【引导炮弹】
CbulletGuide::CbulletGuide()
{  
	v0=0;
	exist=0;
	bombOrNot=0;
	bWidth=BULLETWIDTH;
	bHeight=BULLETHEIGHT;
	bulletName=BULLETGUIDE;
}
void CbulletGuide::fly(CcombatData & combatData,CcombatShower & combatShower)
{ 
	int guideR=100;
	double guideV=40;

	Cpoint bombP;
	double t;//时间
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//计算出炮弹相对于地面的发射角
	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//用于改变子弹的位置
	{
		//判断是否进入引导范围
		for(int i=0;i<PLAYERNUM;i++)
		{
			if(i!=combatData.whoIsPlaying)
			{
				double dr=position.dist(position,combatData.tank[i].position);
				if(dr<guideR)
				{
					//引导过程
					double dx=combatData.tank[i].position.x-position.x;
					double dy=combatData.tank[i].position.y-position.y;
					double cosCita=dx/dr;
					double sinCita=dy/dr;
					while(!judgeCollision((int)position.x,(int)position.y,combatData))
					{
						position.x+=guideV*cosCita;
						position.y+=guideV*sinCita;
						combatShower.show(combatData);
					}
					break;
				}
			}
		}
		//爆炸
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//清除 只改变exsit的值，其它都不要碰
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//调用画图函数
	}
	eliminateBullet();  //直接飞出去的，也清除子弹
}
void CbulletGuide::bomb(CcombatData &combatData,CcombatShower &combatShower)
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
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //游戏中最远的打击距离，主对角线
	for(int i=0;i<PLAYERNUM;i++)
	{
		if(combatData.tank[i].hp>0)
		{
			double launchDist=position.dist(combatData.tank[i].position,combatData.tank[combatData.whoIsPlaying].position);
			double cntDoubleRate=launchDist/maxDist+DOUBLE_DAMAGE_BASIC_RATE;
			int k=rand()%((int)(1.0/cntDoubleRate));  
			if(k==0){combatData.tank[i].gotDoubleDamage=true;}
			double d=position.dist(position,combatData.tank[i].position);
			if(d<=BOMBR)
			{
				int damageK=(combatData.tank[i].gotDoubleDamage==true)? 2:1;
				d=(d<BULLET_COLLISION_R+TANK_COLLISION_R)? (BULLET_COLLISION_R+TANK_COLLISION_R):d;
				combatData.tank[i].changeHpTo((int)(combatData.tank[i].hp-damageK*BOMB_MAX_DAMAGE*(1-d*1.0/BOMBR)),combatData,combatShower);
			}
			combatData.tank[i].gotDoubleDamage=false;
		}
	}
	//cout<<"子弹已经爆炸"<<endl;
}

//【六六合彩弹】
CbulletBet::CbulletBet()
{  
	v0=0;
	exist=0;
	bombOrNot=0;
	bWidth=BULLETWIDTH;
	bHeight=BULLETHEIGHT;
	bulletName=BULLETBET;
}
void CbulletBet::fly(CcombatData & combatData,CcombatShower & combatShower)
{ 
	Cpoint bombP;
	double t;//时间
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//计算出炮弹相对于地面的发射角
	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//用于改变子弹的位置
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//清除 只改变exsit的值，其它都不要碰
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//调用画图函数
	}
	eliminateBullet();  //直接飞出去的，也清除子弹
}
void CbulletBet::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	int betK=3;

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
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //游戏中最远的打击距离，主对角线
	for(int i=0;i<PLAYERNUM;i++)
	{
		if(combatData.tank[i].hp>0)
		{
			double launchDist=position.dist(combatData.tank[i].position,combatData.tank[combatData.whoIsPlaying].position);
			double cntDoubleRate=launchDist/maxDist+DOUBLE_DAMAGE_BASIC_RATE;
			int k=rand()%((int)(1.0/cntDoubleRate));  
			if(k==0){combatData.tank[i].gotDoubleDamage=true;}
			double d=position.dist(position,combatData.tank[i].position);
			if(d<=BOMBR)
			{
				int damageK=(combatData.tank[i].gotDoubleDamage==true)? 2:1;
				int luck=rand()%2;
				if(luck==0){damageK*=betK;}
				else{damageK*=(-betK);}
				d=(d<BULLET_COLLISION_R+TANK_COLLISION_R)? (BULLET_COLLISION_R+TANK_COLLISION_R):d;
				combatData.tank[i].changeHpTo((int)(combatData.tank[i].hp-damageK*BOMB_MAX_DAMAGE*(1-d*1.0/BOMBR)),combatData,combatShower);
			}
			combatData.tank[i].gotDoubleDamage=false;
		}
	}
	//cout<<"子弹已经爆炸"<<endl;
}

//【嗜血连发弹】
CbulletSx::CbulletSx()
{  
	v0=0;
	exist=0;
	bombOrNot=0;
	bWidth=BULLETWIDTH;
	bHeight=BULLETHEIGHT;
	bulletName=BULLETSX;
}
void CbulletSx::fly(CcombatData & combatData,CcombatShower & combatShower)
{ 
	int extraShootNum=rand()%10+1;  // 1-5     五分之三记录3连击，其它都是十分之一
	int sxTotalNum=(1+extraShootNum>5)? 3:(1+extraShootNum);
	double hpCostRate=0.1*(sxTotalNum);


	Cpoint bombP;
	double t;//时间
	for(int num=1;num<=sxTotalNum;num++)
	{
		createBullet(combatData);
		double x0=position.x;
		double y0=position.y;
		double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
		cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//计算出炮弹相对于地面的发射角
		//position.x=x0;
		//position.x=y0;
		for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//用于改变子弹的位置
		{
			if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
			{
				bombOrNot=1;
				eliminateBullet();//清除 只改变exsit的值，其它都不要碰
				combatShower.show(combatData);
				bombOrNot=0;
				bomb(combatData,combatShower);
				combatShower.show(combatData);
				combatData.battleField.putTankToUpSurface(combatData,combatShower);
				break;
			}	
			combatShower.show(combatData);//调用画图函数
		}
		eliminateBullet(); //直接飞出去的，也清除子弹
	}
	combatData.tank[combatData.whoIsPlaying].changeHpTo((int)combatData.tank[combatData.whoIsPlaying].hp*(1-hpCostRate),combatData,combatShower);
}
void CbulletSx::bomb(CcombatData &combatData,CcombatShower &combatShower)
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
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //游戏中最远的打击距离，主对角线
	for(int i=0;i<PLAYERNUM;i++)
	{
		if(combatData.tank[i].hp>0)
		{
			double launchDist=position.dist(combatData.tank[i].position,combatData.tank[combatData.whoIsPlaying].position);
			double cntDoubleRate=launchDist/maxDist+DOUBLE_DAMAGE_BASIC_RATE;
			int k=rand()%((int)(1.0/cntDoubleRate));  
			if(k==0){combatData.tank[i].gotDoubleDamage=true;}
			double d=position.dist(position,combatData.tank[i].position);
			if(d<=BOMBR)
			{
				int damageK=(combatData.tank[i].gotDoubleDamage==true)? 2:1;
				d=(d<BULLET_COLLISION_R+TANK_COLLISION_R)? (BULLET_COLLISION_R+TANK_COLLISION_R):d;
				combatData.tank[i].changeHpTo((int)(combatData.tank[i].hp-damageK*BOMB_MAX_DAMAGE*(1-d*1.0/BOMBR)),combatData,combatShower);
			}
			combatData.tank[i].gotDoubleDamage=false;
		}
	}
	//cout<<"子弹已经爆炸"<<endl;
}


//……………………子弹盒子……………………
void CbulletBox::initTankBullet(CcombatData & combatData)
{
	for(int i=0;i<PLAYERNUM;i++)
	{
		combatData.tank[i].bullet= &combatData.bulletBox.bulletNormal;
	}
}
