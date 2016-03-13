//allBullets.cpp
//include �� ǰ����������.......................................................................
#include "common.h"
#include"allBullets.h"
using namespace std;

//..............................................................................................
 extern int PLAYERNUM;


//����ͨ�ӵ���
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
	double t;//ʱ��
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//������ڵ�����ڵ���ķ����
	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//���ڸı��ӵ���λ��
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//��� ֻ�ı�exsit��ֵ����������Ҫ��
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//���û�ͼ����
	}
	eliminateBullet();  //ֱ�ӷɳ�ȥ�ģ�Ҳ����ӵ�
}
void CbulletNormal::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	//��������Ƿ�ֹը���ڵ�ͼ��Ե��ʱ�������������Σ��
	int modify=5;//��ⷶΧ����һ��
	int xLeft=(int)((position.x-BOMBR-modify<0)? 0:(position.x-BOMBR-modify));
	int xRight=(int)((position.x+BOMBR+modify>BFWIDTH-1)? (BFWIDTH-1):(position.x+BOMBR+modify));
	int yBottom=(int)((position.y-BOMBR-modify<0)? 0:(position.y-BOMBR-modify));
	int yHead=(int)((position.y+BOMBR+modify>BFHEIGHT-1)? (BFHEIGHT-1):(position.y+BOMBR+modify));

	//���´������������ӵ�Ӧ�ñ�ը�ķ�Χ,���ܱ�ըӰ���map����ֵ��ֵΪ0
    combatData.battleField.startChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);
	for(int x=xLeft;x<=xRight;x++)//�������ڿ���
	{
		for(int y=yBottom;y<=yHead;y++)
		{
			  if(combatData.battleField.map[x][y]!=0)    //�ж��ӵ���ը��λ���Ƿ����ڵ��δ�       
			  {
				  if((int)(position.dist(Cpoint(x,y),position)+0.5)<=BOMBR)
				  {  
					 combatData.battleField.changeMapValueTo(x,y,0);
				  }		  
			  }
		}
	}
	combatData.battleField.finishChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);



	//���³������ڼ���̹���Ƿ����ӵ���ը��Χ�ڣ���Ҫ�ı�Ѫ����ֵ
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //��Ϸ����Զ�Ĵ�����룬���Խ���
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
	//cout<<"�ӵ��Ѿ���ը"<<endl;
}

//��˲���ӵ���
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
	double t;//ʱ��
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//������ڵ�����ڵ���ķ����

	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//���ڸı��ӵ���λ��
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//��� ֻ�ı�exsit��ֵ����������Ҫ��
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//���û�ͼ����
		//Sleep(SLEEP_TIME);
	}
	eliminateBullet();  //ֱ�ӷɳ�ȥ�ģ�Ҳ����ӵ�
}
void CbulletBlink::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	combatData.tank[combatData.whoIsPlaying].changePositionTo(position.x,position.y);
}

//��ԭ�ӵ���
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
	double t;//ʱ��
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//������ڵ�����ڵ���ķ����

	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//���ڸı��ӵ���λ��
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//��� ֻ�ı�exsit��ֵ����������Ҫ��
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//���û�ͼ����
		//Sleep(SLEEP_TIME);
	}
	eliminateBullet();  //ֱ�ӷɳ�ȥ�ģ�Ҳ����ӵ�
}
void CbulletNuclear::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	int rk=4; //����ը�뾶������
	//��������Ƿ�ֹը���ڵ�ͼ��Ե��ʱ�������������Σ��
	int modify=5;//��ⷶΧ����һ��
	int xLeft=(int)((position.x-BOMBR*rk-modify<0)? 0:(position.x-BOMBR*rk-modify));
	int xRight=(int)((position.x+BOMBR*rk+modify>BFWIDTH-1)? (BFWIDTH-1):(position.x+BOMBR*rk+modify));
	int yBottom=(int)((position.y-BOMBR*rk-modify<0)? 0:(position.y-BOMBR*rk-modify));
	int yHead=(int)((position.y+BOMBR*rk+modify>BFHEIGHT-1)? (BFHEIGHT-1):(position.y+BOMBR*rk+modify));

	//���´������������ӵ�Ӧ�ñ�ը�ķ�Χ,���ܱ�ըӰ���map����ֵ��ֵΪ0
	combatData.battleField.startChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);
	for(int x=xLeft;x<=xRight;x++)//�������ڿ���
	{
		for(int y=yBottom;y<=yHead;y++)
		{
			  if(combatData.battleField.map[x][y]!=0)    //�ж��ӵ���ը��λ���Ƿ����ڵ��δ�       
			  {
				  if((int)(position.dist(Cpoint(x,y),position)+0.5)<=BOMBR*rk)
				  {  
					 combatData.battleField.changeMapValueTo(x,y,0);
				  }		  
			  }
		}
	}
	combatData.battleField.finishChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);

	//���³������ڼ���̹���Ƿ����ӵ���ը��Χ�ڣ���Ҫ�ı�Ѫ����ֵ
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //��Ϸ����Զ�Ĵ�����룬���Խ���
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
	//cout<<"�ӵ��Ѿ���ը"<<endl;
}

//�������ڵ���
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
	double t;//ʱ��
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//������ڵ�����ڵ���ķ����
	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//���ڸı��ӵ���λ��
	{
		//�ж��Ƿ����������Χ
		for(int i=0;i<PLAYERNUM;i++)
		{
			if(i!=combatData.whoIsPlaying)
			{
				double dr=position.dist(position,combatData.tank[i].position);
				if(dr<guideR)
				{
					//��������
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
		//��ը
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//��� ֻ�ı�exsit��ֵ����������Ҫ��
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//���û�ͼ����
	}
	eliminateBullet();  //ֱ�ӷɳ�ȥ�ģ�Ҳ����ӵ�
}
void CbulletGuide::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	//��������Ƿ�ֹը���ڵ�ͼ��Ե��ʱ�������������Σ��
	int modify=5;//��ⷶΧ����һ��
	int xLeft=(int)((position.x-BOMBR-modify<0)? 0:(position.x-BOMBR-modify));
	int xRight=(int)((position.x+BOMBR+modify>BFWIDTH-1)? (BFWIDTH-1):(position.x+BOMBR+modify));
	int yBottom=(int)((position.y-BOMBR-modify<0)? 0:(position.y-BOMBR-modify));
	int yHead=(int)((position.y+BOMBR+modify>BFHEIGHT-1)? (BFHEIGHT-1):(position.y+BOMBR+modify));

	//���´������������ӵ�Ӧ�ñ�ը�ķ�Χ,���ܱ�ըӰ���map����ֵ��ֵΪ0
    combatData.battleField.startChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);
	for(int x=xLeft;x<=xRight;x++)//�������ڿ���
	{
		for(int y=yBottom;y<=yHead;y++)
		{
			  if(combatData.battleField.map[x][y]!=0)    //�ж��ӵ���ը��λ���Ƿ����ڵ��δ�       
			  {
				  if((int)(position.dist(Cpoint(x,y),position)+0.5)<=BOMBR)
				  {  
					 combatData.battleField.changeMapValueTo(x,y,0);
				  }		  
			  }
		}
	}
	combatData.battleField.finishChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);



	//���³������ڼ���̹���Ƿ����ӵ���ը��Χ�ڣ���Ҫ�ı�Ѫ����ֵ
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //��Ϸ����Զ�Ĵ�����룬���Խ���
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
	//cout<<"�ӵ��Ѿ���ը"<<endl;
}

//�������ϲʵ���
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
	double t;//ʱ��
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//������ڵ�����ڵ���ķ����
	position.x=x0;
	position.x=y0;;
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//���ڸı��ӵ���λ��
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//��� ֻ�ı�exsit��ֵ����������Ҫ��
			combatShower.show(combatData);
			bombOrNot=0;
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//���û�ͼ����
	}
	eliminateBullet();  //ֱ�ӷɳ�ȥ�ģ�Ҳ����ӵ�
}
void CbulletBet::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	int betK=3;

	//��������Ƿ�ֹը���ڵ�ͼ��Ե��ʱ�������������Σ��
	int modify=5;//��ⷶΧ����һ��
	int xLeft=(int)((position.x-BOMBR-modify<0)? 0:(position.x-BOMBR-modify));
	int xRight=(int)((position.x+BOMBR+modify>BFWIDTH-1)? (BFWIDTH-1):(position.x+BOMBR+modify));
	int yBottom=(int)((position.y-BOMBR-modify<0)? 0:(position.y-BOMBR-modify));
	int yHead=(int)((position.y+BOMBR+modify>BFHEIGHT-1)? (BFHEIGHT-1):(position.y+BOMBR+modify));

	//���´������������ӵ�Ӧ�ñ�ը�ķ�Χ,���ܱ�ըӰ���map����ֵ��ֵΪ0
    combatData.battleField.startChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);
	for(int x=xLeft;x<=xRight;x++)//�������ڿ���
	{
		for(int y=yBottom;y<=yHead;y++)
		{
			  if(combatData.battleField.map[x][y]!=0)    //�ж��ӵ���ը��λ���Ƿ����ڵ��δ�       
			  {
				  if((int)(position.dist(Cpoint(x,y),position)+0.5)<=BOMBR)
				  {  
					 combatData.battleField.changeMapValueTo(x,y,0);
				  }		  
			  }
		}
	}
	combatData.battleField.finishChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);



	//���³������ڼ���̹���Ƿ����ӵ���ը��Χ�ڣ���Ҫ�ı�Ѫ����ֵ
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //��Ϸ����Զ�Ĵ�����룬���Խ���
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
	//cout<<"�ӵ��Ѿ���ը"<<endl;
}

//����Ѫ��������
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
	int extraShootNum=rand()%10+1;  // 1-5     ���֮����¼3��������������ʮ��֮һ
	int sxTotalNum=(1+extraShootNum>5)? 3:(1+extraShootNum);
	double hpCostRate=0.1*(sxTotalNum);


	Cpoint bombP;
	double t;//ʱ��
	for(int num=1;num<=sxTotalNum;num++)
	{
		createBullet(combatData);
		double x0=position.x;
		double y0=position.y;
		double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
		cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//������ڵ�����ڵ���ķ����
		//position.x=x0;
		//position.x=y0;
		for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//���ڸı��ӵ���λ��
		{
			if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
			{
				bombOrNot=1;
				eliminateBullet();//��� ֻ�ı�exsit��ֵ����������Ҫ��
				combatShower.show(combatData);
				bombOrNot=0;
				bomb(combatData,combatShower);
				combatShower.show(combatData);
				combatData.battleField.putTankToUpSurface(combatData,combatShower);
				break;
			}	
			combatShower.show(combatData);//���û�ͼ����
		}
		eliminateBullet(); //ֱ�ӷɳ�ȥ�ģ�Ҳ����ӵ�
	}
	combatData.tank[combatData.whoIsPlaying].changeHpTo((int)combatData.tank[combatData.whoIsPlaying].hp*(1-hpCostRate),combatData,combatShower);
}
void CbulletSx::bomb(CcombatData &combatData,CcombatShower &combatShower)
{
	//��������Ƿ�ֹը���ڵ�ͼ��Ե��ʱ�������������Σ��
	int modify=5;//��ⷶΧ����һ��
	int xLeft=(int)((position.x-BOMBR-modify<0)? 0:(position.x-BOMBR-modify));
	int xRight=(int)((position.x+BOMBR+modify>BFWIDTH-1)? (BFWIDTH-1):(position.x+BOMBR+modify));
	int yBottom=(int)((position.y-BOMBR-modify<0)? 0:(position.y-BOMBR-modify));
	int yHead=(int)((position.y+BOMBR+modify>BFHEIGHT-1)? (BFHEIGHT-1):(position.y+BOMBR+modify));

	//���´������������ӵ�Ӧ�ñ�ը�ķ�Χ,���ܱ�ըӰ���map����ֵ��ֵΪ0
    combatData.battleField.startChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);
	for(int x=xLeft;x<=xRight;x++)//�������ڿ���
	{
		for(int y=yBottom;y<=yHead;y++)
		{
			  if(combatData.battleField.map[x][y]!=0)    //�ж��ӵ���ը��λ���Ƿ����ڵ��δ�       
			  {
				  if((int)(position.dist(Cpoint(x,y),position)+0.5)<=BOMBR)
				  {  
					 combatData.battleField.changeMapValueTo(x,y,0);
				  }		  
			  }
		}
	}
	combatData.battleField.finishChangeMapValue(xLeft,yBottom,xRight,yHead,combatData);



	//���³������ڼ���̹���Ƿ����ӵ���ը��Χ�ڣ���Ҫ�ı�Ѫ����ֵ
	double maxDist=sqrt((double)(BFHEIGHT*BFHEIGHT+BFWIDTH*BFWIDTH));   //��Ϸ����Զ�Ĵ�����룬���Խ���
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
	//cout<<"�ӵ��Ѿ���ը"<<endl;
}


//�����������������ӵ����ӡ���������������
void CbulletBox::initTankBullet(CcombatData & combatData)
{
	for(int i=0;i<PLAYERNUM;i++)
	{
		combatData.tank[i].bullet= &combatData.bulletBox.bulletNormal;
	}
}
