#include "common.h"
using namespace std;

CgameProcessor gameProcessor;//我是全局变量哦

void main()
{
	gameProcessor.changeGameProcessTo(MAIN_UI); 
	system("pause");
}
