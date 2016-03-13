//CbattleField.h
#ifndef _CBATTLEFIELD_H_
#define _CBATTLEFIELD_H_

#define BFWIDTH (1000)
#define BFHEIGHT (600)
//include �� ǰ����������.......................................................................
#include "common.h"



//..............................................................................................


class CbattleField
{
public:
	CbattleField();
	~CbattleField();
	void initMap(CcombatData &combatData);
	
	void changeUpSurface1to2(int x1,int y1,int x2,int y2,CcombatData &combatData);  //�ѵ�ͼһ���η�Χ������λ���ϱ����1���ֵת��2.����ʶ������ϱ��档
	int getUpSurfaceY(Cpoint &eventP,CcombatData &combatData); //��һ���㣬�����ڸõ�X��λ���ϸ������ϱ����Y������-����2�ĵ�
	double getUpSurfaceCita(Cpoint &p,CcombatData &combatData); //��һ���㣬�����ڸõ�����߽�(0��PI)��ǰ����ȷ���õ��mapֵ��2�����ϱ��棡
	void putTankToUpSurface(CcombatData &combatData,CcombatShower & combatShower);//�������������ȽϺá���Ϊһ�α�ը����������tank�½���������������tank����
    int changeMapValueTo(int x,int y,int newValue);
    int startChangeMapValue(double xl,double yb,double xr,double yh,CcombatData &combatData);
	int finishChangeMapValue(double xl,double yb,double xr,double yh,CcombatData &combatData);
	void createMapFromPicture();   //��res�� mapPicture�ļ�������map
    
	int bfWidth,bfHeight;
	int (*map)[BFHEIGHT];
	bool mapChanging;
};
#endif