#ifndef _COMMON_H_
#define _COMMON_H_

//��ͼˢ������
#define UPDATE_T (1)

//����"ջ"���������
#define MAX_PROCESS_NUM (10)
//�������
#define MAX_HANDCARD_NUM (4)
#define MAX_CARD_KIND_NUM (50)
#define DOUBLE_DAMAGE_BASIC_RATE (0.01)  //���������ʣ���ս��ʱ��ı����ʡ�Զ�������мӳɡ�    ȫ���Խ��ߴ����ʱ�򣬱�����1
//��ͼ�����
#define MAP_MAX_NUM (10)

//ԭcombatData.h����
#define PLAYERNUM_MAX (4)        //�����������

//ԭtank.h����
#define PI 3.14159
#define TANKWIDTH 50
#define TANKHEIGHT 50
#define MAXMOVABLECITA (PI*2/5.0)
#define DMOVE (TANKWIDTH/10.0)
#define DCITA (PI/60.0)     //����ÿһ�νǶȱ任��ֵ   
#define TANK_MAX_LAUNCH_CITA (PI*2/5.0)
#define TIMELMT (60)  //ʱ������


//ԭbullet.h����
#define XIAOG 0.00098
#define BULLETWIDTH (TANKWIDTH/2)
#define BULLETHEIGHT (TANKWIDTH/2)
#define DOWN_DT 40  //���������ʱ����   ԭ20
#define SLEEP_TIME 0
#define STRENGTH_TO_V0 0.012
#define BULLET_COLLISION_R (BULLETHEIGHT/2.0)
#define TANK_COLLISION_R (TANKHEIGHT/2.0)
#define BOMBR ((BULLET_COLLISION_R+TANK_COLLISION_R)*1.2)//�ӵ��ı�ը�뾶
#define BOMB_MAX_DAMAGE (100*BOMBR/(BOMBR-BULLET_COLLISION_R+TANK_COLLISION_R))   //��������ײ�������õ�
#define HPBONUS (5)


//���ű�����������Ҫ��ӵ�
#pragma comment(lib,"Winmm.lib")



//��������
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
//�����ȵ� дȫ


//�����Ϸ����
enum GameProcess{
	NOPROCESS,
	LOADING,  //����LOADING��ʱ��
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

//�Զ���ս��״̬ö������
enum CombatState{
	COMBAT_INITIAL,
	BREAK/*��ͣ*/,
	COMBAT_END,
	ROUND_START_STAGE,
	ROUND_END_STAGE,
	PLAYER_START_STAGE,
	DEAL_CARD_STAGE,
	ACTING_STAGE,
	ABANDONED_CARD_STAGE,
	PLAYER_END_STAGE
};

//�ӵ�����
enum BulletName{
	BULLETBASE,
	BULLETNORMAL,
	BULLETBLINK,
	BULLETNUCLEAR,
	BULLETGUIDE,
	BULLETBET,
	BULLETSX
};

//��Ƭ����
enum CardName{
	NONAME,
	BLINK,
	NUCLEAR,
	GUIDE,
	BET,
	SX,
	HEAL,
	LUNAHEAL,//��������
	RELOAD,//����װ
	CRITSPACE,//�ױ��ռ俨
	CARDSWEEP,//����Ĩɱ
	THUNDERSTORM,//�����籩
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

//��IPT�����include��˳���н�����   ����tank�õ�bullet��bulletҪ��ǰ�棡
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
