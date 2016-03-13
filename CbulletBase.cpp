//CbulletBase.cpp
//include �� ǰ����������.......................................................................
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
	v0=(combatData.tank[combatData.whoIsPlaying].launchStrength)*(STRENGTH_TO_V0);  //������ϵ����ʱ����
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



//�����������������������������������������˺��������ӵ����ƶ��켣����Ҫ�ı��ӵ���λ�á���������������������������������������
void CbulletBase::fly(CcombatData & combatData,CcombatShower & combatShower)
{ 
	Cpoint bombP;
	double t;//ʱ��
	double x0=position.x;
	double y0=position.y;
	double cita=combatData.tank[combatData.whoIsPlaying].launchCita+combatData.tank[combatData.whoIsPlaying].tankCita;
	cita=(combatData.tank[combatData.whoIsPlaying].tankDirection==1)? cita:(PI-cita);//������ڵ�����ڵ���ķ����

	//���ڷ����һ˲���Ԥ�г���ը�㡿������ը��һ˲�俨
	//bombP.reset(0,0);
	//for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//���ڸı��ӵ���λ��
	//{
	//	if(judgeCollision((int)position.x,(int)position.y,combatData))
	//	{
	//		bombP.reset(position.x,position.y);
	//		break;
	//	}
	//}

	//�����������������̵ķ�ӳ��
	position.x=x0;
	position.x=y0;;
	//combatShower.show(combatData);
	for(t=0;changePositionTo(x0+v0*cos(cita)*t,y0+v0*sin(cita)*t-0.5*XIAOG*t*t); t+=DOWN_DT)//���ڸı��ӵ���λ��
	{
		if(judgeCollision((int)position.x,(int)position.y,combatData)/*position.dist(position,bombP)==0*/)
		{
			bombOrNot=1;
			eliminateBullet();//��� ֻ�ı�exsit��ֵ����������Ҫ��
			combatShower.show(combatData);
			bomb(combatData,combatShower);
			combatShower.show(combatData);
			bombOrNot=0;
			combatData.battleField.putTankToUpSurface(combatData,combatShower);
			break;
		}	
		combatShower.show(combatData);//���û�ͼ����
		//Sleep(SLEEP_TIME);
	}
	eliminateBullet();  //ֱ�ӷɳ�ȥ�ģ�Ҳ����ӵ�
}



//�����������������������������������������ӵ��ı�ը����������ͼ��Ϣ���ӵ���λ�ý�������ˡ�����������
void CbulletBase::bomb(CcombatData &combatData,CcombatShower &combatShower)
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
	//cout<<"�ӵ��Ѿ���ը"<<endl;
}

int CbulletBase::changePositionTo(double newx,double newy)   //�ӵ������������ɵģ���Ϊ���漰map�������
{
	if(newx<0 || newx>=BFWIDTH || newy<0)  //y�������ޣ������ɵ����Ͽ��Ի���
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
	//��Ҫ���͵������ײ������ײ���
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

	//��Ҫ����tank����ײ��������ײ���
	for(int i=0;i<PLAYERNUM;i++)
	{
		if(combatData.tank[i].hp>0 && i!=combatData.whoIsPlaying) //����ը�Լ�
		{
			if(position.dist(position,combatData.tank[i].position)<=BULLET_COLLISION_R+TANK_COLLISION_R)
			{
				return true;
			}
		}
	}
	return false;
}
