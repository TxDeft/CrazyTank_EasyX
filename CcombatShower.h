#ifndef _CCOMBATSHOWER_H
#define _CCOMBATSHOWER_H
#define ROT_CONST 120/70
#include"common.h"

using namespace std;

class CcombatShower//最后对象名为  combatshower
{
public:
	void show(const CcombatData &combatData);//调用接口
	void showMap(const CcombatData &combatData);//显示地图函数 依旧引用传参
	void showTank(const CcombatData &combatData);//
	void showBullet(const CcombatData &combatData);
	void showInfo(const CcombatData &combatData);
	void eliminateBoundary(IMAGE &image,int imageX, int imageY,int imageWidth,int imageHeight);//自己写的去除方形图片周围黑边的函数（可改进为传入对象）
	void numChangeImage(int number,int imageX,int imageY);//提供字体库不完整 写出一个整形数字转为图片的函数
	void eliminateBoundary_bomb(IMAGE &image,int imageX, int imageY,int imageWidth,int imageHeight);//需要渐变效果，所以重写一个 刚开始想用重载，怕引起歧义~重写
	void showControlPanel(const CcombatData &combatData);//显示控制面板
	void showCardPanel(const CcombatData &combatData);
	void open(const CcombatData &combatData);//开启画图函数
	void close();//关闭画图函数
	IMAGE backgroundImage;//收获：读取图片loadimage是与硬盘做交流所以 为了注重效率，把对于地图的读取拿到class以及开始函数中，大大提升了运行效率
	IMAGE earthImage;
	IMAGE tankImageR,tankImageL,tank_rot;
	IMAGE tomb_temp;
	IMAGE blood_back;
	IMAGE blood_temp;
	IMAGE plus_temp,decrease_temp;
	IMAGE name1,name2,name3,name4;
	IMAGE bulletImage_temp;
	IMAGE bomb_temp;
	IMAGE crit_temp;
	IMAGE controlpanel_player1,controlpanel_player2,controlpanel_player3,controlpanel_player4;
	IMAGE round;
	IMAGE help_temp;
	IMAGE power_temp;
	IMAGE energy_temp;
	IMAGE cardpanel;
	IMAGE num[10];
	//-------------------------------以下是地图生动小动画 依旧是静态 但是用static 独立数据来完成绘图----------------------------------
	void flashPlayer(const CcombatData &combatData);
	IMAGE flashplayer;
	void flyBird();
	IMAGE bird_temp;




	//-------------------------------以下是游戏流程游戏状态一类的谁赢了 谁输了xxx的----------------------------------
	void nextPlayer(const CcombatData &combatData);
	IMAGE next_temp;
	void end_Cartoon(const CcombatData &combatData);
	//------------------------------------------------卡片相关-------------------------------------------------------
	IMAGE card_blink;
	IMAGE blink;
	IMAGE card_nuclear;
	IMAGE nuclear;
	IMAGE card_cure;
	IMAGE card_guide,card_bet,card_sx,card_lunaheal,card_reload,card_critspace,card_cardsweep,card_thunderstorm,card_barrier;
	IMAGE card_unknown;
	IMAGE card_light;
	IMAGE card_left_temp;
	void cardTransform(IMAGE &img,CardName cardname);

};
#endif
