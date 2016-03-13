#ifndef _CCOMBATSHOWER_H
#define _CCOMBATSHOWER_H
#define ROT_CONST 120/70
#include"common.h"

using namespace std;

class CcombatShower//��������Ϊ  combatshower
{
public:
	void show(const CcombatData &combatData);//���ýӿ�
	void showMap(const CcombatData &combatData);//��ʾ��ͼ���� �������ô���
	void showTank(const CcombatData &combatData);//
	void showBullet(const CcombatData &combatData);
	void showInfo(const CcombatData &combatData);
	void eliminateBoundary(IMAGE &image,int imageX, int imageY,int imageWidth,int imageHeight);//�Լ�д��ȥ������ͼƬ��Χ�ڱߵĺ������ɸĽ�Ϊ�������
	void numChangeImage(int number,int imageX,int imageY);//�ṩ����ⲻ���� д��һ����������תΪͼƬ�ĺ���
	void eliminateBoundary_bomb(IMAGE &image,int imageX, int imageY,int imageWidth,int imageHeight);//��Ҫ����Ч����������дһ�� �տ�ʼ�������أ�����������~��д
	void showControlPanel(const CcombatData &combatData);//��ʾ�������
	void showCardPanel(const CcombatData &combatData);
	void open(const CcombatData &combatData);//������ͼ����
	void close();//�رջ�ͼ����
	IMAGE backgroundImage;//�ջ񣺶�ȡͼƬloadimage����Ӳ������������ Ϊ��ע��Ч�ʣ��Ѷ��ڵ�ͼ�Ķ�ȡ�õ�class�Լ���ʼ�����У��������������Ч��
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
	//-------------------------------�����ǵ�ͼ����С���� �����Ǿ�̬ ������static ������������ɻ�ͼ----------------------------------
	void flashPlayer(const CcombatData &combatData);
	IMAGE flashplayer;
	void flyBird();
	IMAGE bird_temp;




	//-------------------------------��������Ϸ������Ϸ״̬һ���˭Ӯ�� ˭����xxx��----------------------------------
	void nextPlayer(const CcombatData &combatData);
	IMAGE next_temp;
	void end_Cartoon(const CcombatData &combatData);
	//------------------------------------------------��Ƭ���-------------------------------------------------------
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
