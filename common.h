#ifndef _COMMON_H_
#define _COMMON_H_

//画图刷新周期
#define UPDATE_T (1)

//流程"栈"的最大容量
#define MAX_PROCESS_NUM (10)
//卡牌相关
#define MAX_HANDCARD_NUM (4)
#define MAX_CARD_KIND_NUM (50)
#define DOUBLE_DAMAGE_BASIC_RATE (0.01)  //基础暴击率，近战的时候的暴击率。远距离打击有加成。    全屏对角线打击的时候，暴击率1
//地图最大数
#define MAP_MAX_NUM (10)

//原combatData.h部分
#define PLAYERNUM_MAX (4)        //定义玩家数量

//原tank.h部分
#define PI 3.14159
#define TANKWIDTH 50
#define TANKHEIGHT 50
#define MAXMOVABLECITA (PI*2/5.0)
#define DMOVE (TANKWIDTH/10.0)
#define DCITA (PI/60.0)     //定义每一次角度变换的值   
#define TANK_MAX_LAUNCH_CITA (PI*2/5.0)
#define TIMELMT (60)  //时间限制


//原bullet.h部分
#define XIAOG 0.00098
#define BULLETWIDTH (TANKWIDTH/2)
#define BULLETHEIGHT (TANKWIDTH/2)
#define DOWN_DT 40  //自由落体的时间间隔   原20
#define SLEEP_TIME 0
#define STRENGTH_TO_V0 0.012
#define BULLET_COLLISION_R (BULLETHEIGHT/2.0)
#define TANK_COLLISION_R (TANKHEIGHT/2.0)
#define BOMBR ((BULLET_COLLISION_R+TANK_COLLISION_R)*1.2)//子弹的爆炸半径
#define BOMB_MAX_DAMAGE (100*BOMBR/(BOMBR-BULLET_COLLISION_R+TANK_COLLISION_R))   //由两个碰撞体积计算得到
#define HPBONUS (5)


//播放背景音乐所需要添加的
#pragma comment(lib,"Winmm.lib")



//按键设置
#define KEY_Up1 w
#define KEY_Up2 w
#define KEY_DOWN1 s
#define KEY_DOWN2 S
#define KEY_LEFT1 a
#define KEY_LEFT2 A
#define KEY_RIGHT1 d
#define KEY_RIGHT2 D

#define KEY_COMBAT_END1 q
#define KEY_COMBAT_END2 Q
#define KEY_PLAYER_END1 e
#define KEY_PLAYER_END2 E
//……等等 写全


//大的游戏进程
enum GameProcess{
	NOPROCESS,
	LOADING,  //各种LOADING的时候
	MAIN_UI,
	START_COMBAT,
	COMBAT,
	COMBAT_BREAK,
	RESTART_COMBAT,
	OPTION,
	REPLAY,
	GAME_INTRODUCTION,
	ABOUT_US,
	EXIT	
};

//自定义战斗状态枚举类型
enum CombatState{
	COMBAT_INITIAL,
	BREAK/*暂停*/,
	COMBAT_END,
	ROUND_START_STAGE,
	ROUND_END_STAGE,
	PLAYER_START_STAGE,
	DEAL_CARD_STAGE,
	ACTING_STAGE,
	ABANDONED_CARD_STAGE,
	PLAYER_END_STAGE
};

//子弹名称
enum BulletName{
	BULLETBASE,
	BULLETNORMAL,
	BULLETBLINK,
	BULLETNUCLEAR,
	BULLETGUIDE,
	BULLETBET,
	BULLETSX
};

//卡片名称
enum CardName{
	NONAME,
	BLINK,
	NUCLEAR,
	GUIDE,
	BET,
	SX,
	HEAL,
	LUNAHEAL,//月神拯救
	RELOAD,//再填装
	CRITSPACE,//易爆空间卡
	CARDSWEEP,//卡牌抹杀
	THUNDERSTORM,//雷霆风暴
	BARRIER
};

#include<cmath>
#include<cstring>
#include <string>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>

class Cpoint;
class Ctank;
class CbulletBase;
class CbulletNormal;
class CbulletBlink;
class CbulletNuclear;
class CbulletBox;
class CcardBase;
class CcardBlink;
class CcardNuclear;
class CcardBox;
class CbattleField;
class CcombatData;
class CcombatShower;
class CgameProcessor;

//【IPT】这个include的顺序有讲究！   比如tank用到bullet，bullet要在前面！
#include"Cpoint.h"
#include"CbulletBase.h"
#include"allBullets.h"
#include"CcardBase.h"
#include"allCards.h"
#include"Ctank.h"
#include"CbattleField.h"
#include"CcombatData.h"
#include"CcombatShower.h"
#include"CgameProcessor.h"


#endif
