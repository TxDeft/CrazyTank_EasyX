//CbattleField.h
#ifndef _CBATTLEFIELD_H_
#define _CBATTLEFIELD_H_

#define BFWIDTH (1000)
#define BFHEIGHT (600)
//include 和 前向引用声明.......................................................................
#include "common.h"



//..............................................................................................


class CbattleField
{
public:
	CbattleField();
	~CbattleField();
	void initMap(CcombatData &combatData);
	
	void changeUpSurface1to2(int x1,int y1,int x2,int y2,CcombatData &combatData);  //把地图一矩形范围内所有位于上表面的1点的值转成2.方便识别查找上表面。
	int getUpSurfaceY(Cpoint &eventP,CcombatData &combatData); //给一个点，返回在该点X的位置上附近的上表面的Y的坐标-即是2的点
	double getUpSurfaceCita(Cpoint &p,CcombatData &combatData); //给一个点，返回在该点的切线角(0，PI)。前提是确保该点的map值是2，是上表面！
	void putTankToUpSurface(CcombatData &combatData,CcombatShower & combatShower);//这个函数在这里比较好。因为一次爆炸肯能引起多个tank下降。这样处理所有tank即可
    int changeMapValueTo(int x,int y,int newValue);
    int startChangeMapValue(double xl,double yb,double xr,double yh,CcombatData &combatData);
	int finishChangeMapValue(double xl,double yb,double xr,double yh,CcombatData &combatData);
	void createMapFromPicture();   //从res的 mapPicture文件中生成map
    
	int bfWidth,bfHeight;
	int (*map)[BFHEIGHT];
	bool mapChanging;
};
#endif