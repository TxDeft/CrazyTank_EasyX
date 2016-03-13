//gameProcessor.h

#ifndef _CGAMEPROCESSOR_H_
#define _CGAMEPROCESSOR_H_

//include �� ǰ����������.......................................................................
#include "common.h"



//..............................................................................................

class CgameProcessor  //gameProcessor �Լ��͹ܿ��ӻ��ˣ�����ꡣ��Ҫshower
{
public:
	CgameProcessor();
	void changeGameProcessTo(enum GameProcess newGP);
	int findExistProcess(enum GameProcess GP);
	
	void loading_controller(int to1_leave0);
	void main_ui_controller(int to1_leave0);
	void start_combat_controller(int to1_leave0);
	void combat_controller(int to1_leave0);
	void combat_break_controller(int to1_leave0);
	void exit_controller(int to1_leave0);
	
	void option_controller(int to1_leave0);
	//void game_introduction_controller(int to1_leave0);
	//void about_us__controller(int to1_leave0);

	enum GameProcess gameProcesses[MAX_PROCESS_NUM];
	int cntProcessStep;
};

#endif