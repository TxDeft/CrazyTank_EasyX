#include"CcombatShower.h"
#include"common.h"
using namespace std;

extern int PLAYERNUM;
void CcombatShower::show(const CcombatData &combatData){

	static clock_t star=clock();//static 赋初值在以后的循环中赋初值变为无效
	clock_t check=clock();;//

	if(combatData.combatState==COMBAT_END)
	{
		end_Cartoon(combatData);
	}
	if((check-star)%UPDATE_T==0){
		BeginBatchDraw();//消除闪烁函数
		showMap(combatData);

		nextPlayer(combatData);
		showTank(combatData);
		nextPlayer(combatData);
		showBullet(combatData);
		nextPlayer(combatData);
		showControlPanel(combatData);
		nextPlayer(combatData);
		showCardPanel(combatData);
		nextPlayer(combatData);
		if(combatData.mode)
		showInfo(combatData);
		nextPlayer(combatData);
		


		//-------------------------------以下是地图生动小动画 依旧是静态 但是用static 独立数据来完成绘图----------------------------------
		flashPlayer(combatData);
		flyBird();


		//-------------------------------以下是游戏流程游戏状态一类的谁赢了 谁输了xxx的----------------------------------
		nextPlayer(combatData);
		FlushBatchDraw();//开始画图
	}



}

void CcombatShower::open(const CcombatData &combatData){
	initgraph(BFWIDTH, BFHEIGHT);//用战场常量初始化图形界面
	
	// 获得窗口句柄
	HWND hWnd = GetHWnd();
	// 使用 API 函数修改窗口名称
	SetWindowText(hWnd, "战斗中...【疯狂坦克DIY】 Made by SAT");

	loadimage(&earthImage,"res\\map\\cntMap\\earth.bmp",BFWIDTH,BFHEIGHT);
	loadimage(&backgroundImage,"res\\map\\cntMap\\background.bmp",BFWIDTH,BFHEIGHT);//背景与地图都拉伸到最大 提高效率在开始时只读一遍背景与地形
	loadimage(&tankImageR,"res\\picture\\tankR.bmp",TANKWIDTH*ROT_CONST,TANKHEIGHT*ROT_CONST);
	loadimage(&tankImageL,"res\\picture\\tankL.bmp",TANKWIDTH*ROT_CONST,TANKHEIGHT*ROT_CONST);
	loadimage(&tomb_temp,"res\\picture\\tomb.bmp",TANKWIDTH*ROT_CONST,TANKHEIGHT*ROT_CONST);
	loadimage(&blood_back,"res\\picture\\blood_back.bmp",TANKWIDTH,7);
	loadimage(&blood_temp,"res\\picture\\blood.bmp",TANKWIDTH,7);
	loadimage(&name1,"res\\picture\\player1.bmp",50,50);
	loadimage(&name2,"res\\picture\\player2.bmp",50,50);
	loadimage(&name3,"res\\picture\\player3.bmp",50,50);
	loadimage(&name4,"res\\picture\\player4.bmp",50,50);
	loadimage(&bomb_temp,"res\\picture\\explosion.bmp",(int)BOMBR+15,(int)BOMBR+15);
	loadimage(&crit_temp,"res\\picture\\crit.bmp",102,102);
	loadimage(&bulletImage_temp,"res\\picture\\bullet.bmp",BULLETWIDTH,BULLETHEIGHT);	
	loadimage(&controlpanel_player1,"res\\picture\\control_player1.bmp",800,175);
	loadimage(&controlpanel_player2,"res\\picture\\control_player2.bmp",800,175);
	loadimage(&controlpanel_player3,"res\\picture\\control_player3.bmp",800,175);
	loadimage(&controlpanel_player4,"res\\picture\\control_player4.bmp",800,175);
	loadimage(&round,"res\\picture\\round.bmp",88,19);
	loadimage(&help_temp,"res\\picture\\help.bmp",138,57);
	loadimage(&power_temp,"res\\picture\\power.bmp",500,15);
	loadimage(&energy_temp,"res\\picture\\energy.bmp",460,15);
	loadimage(&cardpanel,"res\\picture\\cardpanel.bmp",63,313);
	loadimage(&num[0],"res\\picture\\number\\0.bmp",25,25);
	loadimage(&num[1],"res\\picture\\number\\1.bmp",25,25);
	loadimage(&num[2],"res\\picture\\number\\2.bmp",25,25);
	loadimage(&num[3],"res\\picture\\number\\3.bmp",25,25);
	loadimage(&num[4],"res\\picture\\number\\4.bmp",25,25);
	loadimage(&num[5],"res\\picture\\number\\5.bmp",25,25);
	loadimage(&num[6],"res\\picture\\number\\6.bmp",25,25);
	loadimage(&num[7],"res\\picture\\number\\7.bmp",25,25);
	loadimage(&num[8],"res\\picture\\number\\8.bmp",25,25);
	loadimage(&num[9],"res\\picture\\number\\9.bmp",25,25);
	loadimage(&plus_temp,"res\\picture\\number\\+.bmp",25,25);
	loadimage(&decrease_temp,"res\\picture\\number\\-.bmp",25,25);
	//-------------------------------卡片相关----------------------------------
	loadimage(&card_blink,"res\\picture\\card\\blink.bmp",63,79);
	loadimage(&blink,"res\\picture\\blink.bmp",100,20);
	loadimage(&card_nuclear,"res\\picture\\card\\nuclear.bmp",63,79);
	loadimage(&nuclear,"res\\picture\\nuclear.bmp",500,500);
	loadimage(&card_cure,"res\\picture\\card\\cure.bmp",63,79);
	loadimage(&card_unknown,"res\\picture\\card\\card_known.bmp",63,79);
	loadimage(&card_light,"res\\picture\\card\\light.bmp",63,79);
	loadimage(&card_left_temp,"res\\picture\\card\\TotalCardNum.bmp");
	loadimage(&card_guide,"res\\picture\\card\\guide.bmp",63,79);
	loadimage(&card_bet,"res\\picture\\card\\FateBit.bmp",63,79);
	loadimage(&card_sx,"res\\picture\\card\\sx.jpg",63,79);
	loadimage(&card_lunaheal,"res\\picture\\card\\LunaHeal.bmp",63,79);
    loadimage(&card_reload,"res\\picture\\card\\reload.bmp",63,79);
	loadimage(&card_critspace,"res\\picture\\card\\critspace.bmp",63,79);
	loadimage(&card_cardsweep,"res\\picture\\card\\SweepCard.bmp",63,79);
	loadimage(&card_thunderstorm,"res\\picture\\card\\ThunderShock.bmp",63,79);
	loadimage(&card_barrier,"res\\picture\\card\\defence.bmp",63,79);




	//-------------------------------以下是地图生动小动画 依旧是静态 但是用static 独立数据来完成绘图----------------------------------
	loadimage(&flashplayer,"res\\picture\\flashPlayer.bmp",50,50);
	loadimage(&bird_temp,"res\\picture\\bird.bmp",25,25);
	//-------------------------------以下是游戏流程游戏状态一类的谁赢了 谁输了xxx的----------------------------------
	loadimage(&next_temp,"res\\picture\\next.bmp",BFWIDTH,BFHEIGHT);


	// 打开音乐
	mciSendString("open res\\map\\cntMap\\backgroundMusic.mp3 alias mymusic", NULL, 0, NULL);
	// 播放音乐
	//mciSendString("play  mymusic", NULL, 0, NULL);
	mciSendString("play mymusic repeat", NULL, 0, NULL);


}

void CcombatShower::close(){
	EndBatchDraw();//现在也不知道这东西什么用处

	//停止音乐
	mciSendString("stop mymusic", NULL, 0, NULL);
	//关闭音乐
	mciSendString("close mymusic", NULL, 0, NULL);

	closegraph();          // 关闭图形界面
}

//························通用小函数····························
//````````````````````````````````去除图片 包括坦克 炮弹的黑边`````````````````````````````````````````````````````
void CcombatShower::eliminateBoundary(IMAGE &image, int imageX, int imageY, int imageWidth, int imageHeight){
	IMAGE background;//创建一个临时对象
	getimage(&background,imageX,imageY,imageWidth,imageHeight);//获取检验区域图像，准备去除
	DWORD* image_back=GetImageBuffer(&image);//分别创建指向
	DWORD* background_back=GetImageBuffer(&background);
	for(int i=0;i<imageWidth*imageHeight;i++)
		if(GetBValue(image_back[i])==0&&GetGValue(image_back[i])==0)
			image_back[i]=background_back[i];
}
void CcombatShower::eliminateBoundary_bomb(IMAGE &image,int imageX, int imageY,int imageWidth,int imageHeight){//需要渐变
	IMAGE background;//创建一个临时对象
	getimage(&background,imageX,imageY,imageWidth,imageHeight);//获取检验区域图像，准备去除
	DWORD* image_back=GetImageBuffer(&image);//分别创建指向
	DWORD* background_back=GetImageBuffer(&background);
	for(int i=0;i<imageWidth*imageHeight;i++)
		if((GetBValue(image_back[i])<=50)&&(GetGValue(image_back[i])<=50))
			image_back[i]=background_back[i];

}
//````````````````````````````````````整形数字边图形````````````````````````````````````
void CcombatShower::numChangeImage(int number,int imageX,int imageY){//PRIDE ~~~~传入整形数字还有需要的坐标 即可画出图形样式的数字~~~~~~~~~~~~
	if(number>=0&&number<=9){
		IMAGE numberS;
		numberS=num[number];
		eliminateBoundary(numberS,imageX,imageY,25,25);
		putimage(imageX,imageY,&numberS);

	}
	else if(number<=99){
		IMAGE numberD1,numberD2;
		numberD1=num[number/10];
		numberD2=num[number-(number/10)*10];
		eliminateBoundary(numberD1,imageX,imageY,25,25);
		putimage(imageX,imageY,&numberD1);
		eliminateBoundary(numberD2,imageX+12,imageY,25,25);
		putimage(imageX+12,imageY,&numberD2);

	}
	else if(number<=999){
		IMAGE numberT1,numberT2,numberT3;
		numberT1=num[number/100];
		numberT2=num[number/10-(number/100)*10];
		numberT3=num[number-(number/10)*10];
		eliminateBoundary(numberT1,imageX,imageY,25,25);
		putimage(imageX,imageY,&numberT1);
		eliminateBoundary(numberT2,imageX+12,imageY,25,25);
		putimage(imageX+12,imageY,&numberT2);
		eliminateBoundary(numberT3,imageX+24,imageY,25,25);
		putimage(imageX+24,imageY,&numberT3);

	}
	else if(number<=9999){
		IMAGE numberQ1,numberQ2,numberQ3,numberQ4;
		numberQ1=num[number/1000];
		numberQ2=num[number/100-(number/1000)*10];
		numberQ3=num[number/10-(number/100)*10];
		numberQ4=num[number-(number/10)*10];
		eliminateBoundary(numberQ1,imageX,imageY,25,25);
		putimage(imageX,imageY,&numberQ1);
		eliminateBoundary(numberQ2,imageX+12,imageY,25,25);
		putimage(imageX+12,imageY,&numberQ2);
		eliminateBoundary(numberQ3,imageX+24,imageY,25,25);
		putimage(imageX+24,imageY,&numberQ3);
		eliminateBoundary(numberQ4,imageX+36,imageY,25,25);
		putimage(imageX+36,imageY,&numberQ4);




	}



}

//````````````````````````````````````停顿小函数代替不靠谱的Sleep()````````````````````````````````````
void wait(float seconds)
{
	clock_t endwait;
	endwait=clock()+seconds*CLK_TCK;
	while(clock()<endwait)
	{}
}
//`````````````````````读地图信息 包括地面背景````````````````````````````
void CcombatShower::showMap(const CcombatData &combatData){







	IMAGE screen(BFWIDTH,BFHEIGHT);
	DWORD* pScreen=GetImageBuffer(&screen);//屏幕的显存指针(为了以后重用加了extern)

	DWORD* pM_background =GetImageBuffer(&backgroundImage);

	DWORD* pM_earth =GetImageBuffer(&earthImage);

	for(int i=0;i<BFWIDTH;i++){
		for(int j=0;j<BFHEIGHT;j++){
			if(combatData.battleField.map[i][j]==1)//如果地图数组的值为1则显示为有地图
				pScreen[(j*BFWIDTH)+i]=pM_earth[(j*BFWIDTH)+i];
			else if(combatData.battleField.map[i][j]==2)
				pScreen[(j*BFWIDTH)+i]=BGR(BLACK);

			else		 //如果地图数组的值为0则显示为无地图 即为显示背景
				pScreen[(j*BFWIDTH)+i]=pM_background[(j*BFWIDTH)+i];
		}
	}


	IMAGE temp(BFWIDTH,BFHEIGHT);
	DWORD* pTemp=GetImageBuffer(&temp);
	for(int i=0;i<BFWIDTH;i++){//做坐标转换 把对称的 y坐标相互对换 只能换一半
		for(int j=0;j<BFHEIGHT/2;j++){

			pTemp[(j*BFWIDTH)+i]=pScreen[(j*BFWIDTH)+i];
			pScreen[(j*BFWIDTH)+i]=pScreen[((BFHEIGHT-1)-j)*BFWIDTH+i];
			pScreen[((BFHEIGHT-1)-j)*1000+i]=pTemp[(j*BFWIDTH)+i];
		}
	}




	putimage(0,0,&screen);

}

//`````````````````````````读坦克相关信息``````````````````````````````````
void CcombatShower::showTank(const CcombatData &combatData){

	for(int i=0;i<PLAYERNUM;i++){
		if(i==combatData.whoIsPlaying)
		{
			continue;												//如果画到正在运行的tank先不要画······最后再画whoIsPlaying的tank的让它遮挡住别的tank


		}

		IMAGE tankImage;
		//···························································
		if(combatData.tank[i].hp<=0){
			tankImage=tomb_temp;
			if(combatData.tank[i].tankDirection==1){

				rotateimage(&tank_rot,&tankImage,combatData.tank[i].tankCita);
			}
			else{

				rotateimage(&tank_rot,&tankImage,0-combatData.tank[i].tankCita);			//此处代码微乱主要加入死后墓碑仍然涉及到墓碑的旋转 朝向 还有坦克底边中心的换算
			}

		}
		else{
			if(combatData.tank[i].tankDirection==1){
				tankImage=tankImageR;
				rotateimage(&tank_rot,&tankImage,combatData.tank[i].tankCita);
			}
			else{
				tankImage=tankImageL;
				rotateimage(&tank_rot,&tankImage,0-combatData.tank[i].tankCita);
			}
		}
		//·····························································

		int real_tx=(int)(combatData.tank[i].position.x-((combatData.tank[i].tkWidth*ROT_CONST)/2));//坐标转换过后的坦克x坐标
		int real_ty=37+(int)((BFHEIGHT-combatData.tank[i].position.y)-(combatData.tank[i].tkHeight*ROT_CONST));//坐标转换过后的坦克y坐标




		eliminateBoundary(tank_rot,real_tx,real_ty,combatData.tank[i].tkWidth*ROT_CONST,combatData.tank[i].tkHeight*ROT_CONST);//去除坦克周围黑色边框

		putimage(real_tx,real_ty,&tank_rot);//读出坦克图片


		//`````````````````````````读出血条`````````````````````

		putimage(real_tx+13,real_ty-5,&blood_back);
		IMAGE blood;
		blood=blood_temp;
		IMAGE background_p;//创建一个临时对象
		getimage(&background_p,real_tx+13,real_ty-5,TANKWIDTH,7);//获取检验区域图像，准备去除
		DWORD* background_back=GetImageBuffer(&background_p);

		DWORD* power_M=GetImageBuffer(&blood);
		for(int p=0;p<(combatData.tank[i].hp/2);p++){
			for(int q=0;q<7;q++){
				background_back[(q*TANKWIDTH)+p]=power_M[(q*TANKWIDTH)+p];
			}
		}

		putimage(real_tx+13,real_ty-5,&background_p);
		//````````````````````````读出玩家姓名````````````````````````````````
		IMAGE name;
		if(i==0)
			name=name1;
		else if(i==1)
			name=name2;
		else if(i==2)
			name=name3;
		else if(i==3)
			name=name4;

		eliminateBoundary(name,real_tx+10,real_ty-55,50,50);
		putimage(real_tx+10,real_ty-55,&name);




	}
	for(int i=0;i<PLAYERNUM;i++){
		if(i!=combatData.whoIsPlaying)
		{
			continue;															//最后来画拥有控制权的tank


		}

		IMAGE tankImage;
		//···························································
		if(combatData.tank[i].hp<=0){
			tankImage=tomb_temp;
			if(combatData.tank[i].tankDirection==1){

				rotateimage(&tank_rot,&tankImage,combatData.tank[i].tankCita);
			}
			else{

				rotateimage(&tank_rot,&tankImage,0-combatData.tank[i].tankCita);			//此处代码微乱主要加入死后墓碑仍然涉及到墓碑的旋转 朝向 还有坦克底边中心的换算
			}

		}
		else{
			if(combatData.tank[i].tankDirection==1){
				tankImage=tankImageR;
				rotateimage(&tank_rot,&tankImage,combatData.tank[i].tankCita);
			}
			else{
				tankImage=tankImageL;
				rotateimage(&tank_rot,&tankImage,0-combatData.tank[i].tankCita);
			}
		}
		//·····························································

		int real_tx=(int)(combatData.tank[i].position.x-((combatData.tank[i].tkWidth*ROT_CONST)/2));//坐标转换过后的坦克x坐标
		int real_ty=37+(int)((BFHEIGHT-combatData.tank[i].position.y)-(combatData.tank[i].tkHeight*ROT_CONST));//坐标转换过后的坦克y坐标




		eliminateBoundary(tank_rot,real_tx,real_ty,combatData.tank[i].tkWidth*ROT_CONST,combatData.tank[i].tkHeight*ROT_CONST);//去除坦克周围黑色边框

		putimage(real_tx,real_ty,&tank_rot);//读出坦克图片



		//`````````````````````````````````读出血条`````````````````````````````````````````

		putimage(real_tx+13,real_ty-5,&blood_back);
		IMAGE blood;
		blood=blood_temp;
		IMAGE background_p;//创建一个临时对象
		getimage(&background_p,real_tx+13,real_ty-5,TANKWIDTH,7);//获取检验区域图像，准备去除
		DWORD* background_back=GetImageBuffer(&background_p);

		DWORD* power_M=GetImageBuffer(&blood);
		for(int p=0;p<(combatData.tank[i].hp/2);p++){
			for(int q=0;q<7;q++){
				background_back[(q*TANKWIDTH)+p]=power_M[(q*TANKWIDTH)+p];
			}
		}

		putimage(real_tx+13,real_ty-5,&background_p);


		//````````````````````````读出玩家姓名````````````````````````````````
		IMAGE name;
		if(i==0)
			name=name1;
		else if(i==1)
			name=name2;
		else if(i==2)
			name=name3;
		else if(i==3)
			name=name4;

		eliminateBoundary(name,real_tx+10,real_ty-55,50,50);
		putimage(real_tx+10,real_ty-55,&name);
	}
}


//```````````````````````````````读炮弹相关信息``````````````````````````````````
void CcombatShower::showBullet(const CcombatData &combatData){
	for(int i=0;i<PLAYERNUM;i++){
		IMAGE bulletImage;
		bulletImage=bulletImage_temp;
		int real_tx=(int)(combatData.tank[i].position.x-((combatData.tank[i].tkWidth*ROT_CONST)/2));//坐标转换过后的坦克x坐标
		int real_ty=37+(int)((BFHEIGHT-combatData.tank[i].position.y)-(combatData.tank[i].tkHeight*ROT_CONST));//坐标转换过后的坦克y坐标


		if(combatData.tank[i].bullet->exist){

			eliminateBoundary(bulletImage,(int)(combatData.tank[i].bullet->position.x-(combatData.tank[i].bullet->bWidth/2)),BULLETHEIGHT/2+(int)((BFHEIGHT-combatData.tank[i].bullet->position.y)-combatData.tank[i].bullet->bHeight),combatData.tank[i].bullet->bWidth,combatData.tank[i].bullet->bHeight);
			putimage((int)(combatData.tank[i].bullet->position.x-(combatData.tank[i].bullet->bWidth/2)),BULLETHEIGHT/2+(int)((BFHEIGHT-combatData.tank[i].bullet->position.y)-combatData.tank[i].bullet->bHeight),&bulletImage);


		}

		if(combatData.tank[i].bullet->bombOrNot){
			IMAGE bomb;
			if(combatData.tank[i].bullet->bulletName==BULLETNUCLEAR)
			{
				bomb=nuclear;
				eliminateBoundary(bomb,-269+(int)(combatData.tank[i].bullet->position.x-(combatData.tank[i].bullet->bWidth/2)),-275+(int)((BFHEIGHT-combatData.tank[i].bullet->position.y)-combatData.tank[i].bullet->bHeight),500,500);
				putimage(-269+(int)(combatData.tank[i].bullet->position.x-(combatData.tank[i].bullet->bWidth/2)),-275+(int)((BFHEIGHT-combatData.tank[i].bullet->position.y)-combatData.tank[i].bullet->bHeight),&bomb);
				FlushBatchDraw();
				wait(0.3);
			}
			else if(combatData.tank[i].bullet->bulletName==BULLETBLINK)
			{
				bomb=blink;
				eliminateBoundary(bomb,-39+(int)(combatData.tank[i].bullet->position.x-(combatData.tank[i].bullet->bWidth/2)),-25+(int)((BFHEIGHT-combatData.tank[i].bullet->position.y)-combatData.tank[i].bullet->bHeight),100,20);
				putimage(-39+(int)(combatData.tank[i].bullet->position.x-(combatData.tank[i].bullet->bWidth/2)),-25+(int)((BFHEIGHT-combatData.tank[i].bullet->position.y)-combatData.tank[i].bullet->bHeight),&bomb);
				FlushBatchDraw();
				wait(0.3);
			}

			else
			{
			bomb=bomb_temp;
			eliminateBoundary(bomb,-19+(int)(combatData.tank[i].bullet->position.x-(combatData.tank[i].bullet->bWidth/2)),-25+(int)((BFHEIGHT-combatData.tank[i].bullet->position.y)-combatData.tank[i].bullet->bHeight),(int)BOMBR+15,(int)BOMBR+15);
			putimage(-19+(int)(combatData.tank[i].bullet->position.x-(combatData.tank[i].bullet->bWidth/2)),-25+(int)((BFHEIGHT-combatData.tank[i].bullet->position.y)-combatData.tank[i].bullet->bHeight),&bomb);
			
			FlushBatchDraw();
            wait(0.05
				);
			}
		}
		if(combatData.tank[i].gotDoubleDamage==1&&combatData.tank[i].hpChange!=0)
		{
			IMAGE crit;
			crit=crit_temp;
			eliminateBoundary(crit,real_tx,real_ty,102,102);
			putimage(real_tx,real_ty,&crit);
			

		}
		
		//```````````````````````````````~做出掉血加血效果~`````````````````````````````````````
		if(combatData.tank[i].hpChange<0){
			
				
			IMAGE decrease;
			decrease=decrease_temp;
			eliminateBoundary(decrease,real_tx+15,real_ty+90,25,25);
			putimage(real_tx+15,real_ty+90,&decrease);
			numChangeImage(abs(combatData.tank[i].hpChange),real_tx+35,real_ty+90);
			
			//



		}
		if(combatData.tank[i].hpChange>0){
			IMAGE plus;
			plus=plus_temp;
			eliminateBoundary(plus,real_tx+15,real_ty+90,25,25);
			putimage(real_tx+15,real_ty+90,&plus);
			numChangeImage(abs(combatData.tank[i].hpChange),real_tx+35,real_ty+90);
			



		}


	}
}


//``````````````````````````````````控制面板````````````````````````````````````````
void CcombatShower::showControlPanel(const CcombatData &combatData){
	int judge=combatData.whoIsPlaying;
	if(judge>=0&&judge<=PLAYERNUM){



		//——————显示主控制板——————
		IMAGE controlpanel;
		if(judge==0)
			controlpanel=controlpanel_player1;
		else if(judge==1)
			controlpanel=controlpanel_player2;
		else if(judge==2)
			controlpanel=controlpanel_player3;
		else if(judge==3)
			controlpanel=controlpanel_player4;




		eliminateBoundary(controlpanel,0,BFHEIGHT-175,800,175);
		putimage(0,BFHEIGHT-175,&controlpanel);
		//————————回合数————————
		IMAGE round_real;
		round_real=round;
		eliminateBoundary(round_real,445,10,88,19);
		putimage(445,10,&round_real);
		numChangeImage(combatData.round,443+88+5,7);
		//———————剩余时间—————————
		numChangeImage(combatData.tank[combatData.whoIsPlaying].timer,485,30);
		//———————帮助显示—————————
		IMAGE help;
		help=help_temp;
		eliminateBoundary(help,1,1,138,57);
		putimage(1,1,&help);


		//——————显示坦克与地面倾斜角————————
		int x0=92,y0=510;//之前量好的圆心坐标
		int xt1,yt1,xt2,yt2;//末位置的坐标
		int radium=80;//之前量好的半径
		judge=combatData.whoIsPlaying;
		if(combatData.tank[judge].tankDirection==1){				
			xt1=(int)(x0+radium*(cos(combatData.tank[judge].tankCita)));
			yt1=(int)(y0-radium*(sin(combatData.tank[judge].tankCita)));
			xt2=(int)(x0-radium*(cos(combatData.tank[judge].tankCita)));
			yt2=(int)(y0+radium*(sin(combatData.tank[judge].tankCita)));
		}
		else{
			xt1=(int)(x0-radium*(cos(combatData.tank[judge].tankCita)));
			yt1=(int)(y0-radium*(sin(combatData.tank[judge].tankCita)));
			xt2=(int)(x0+radium*(cos(combatData.tank[judge].tankCita)));
			yt2=(int)(y0+radium*(sin(combatData.tank[judge].tankCita)));
		}

		setcolor(RGB(128,64, 0));
		setlinestyle(PS_SOLID, NULL, 5);
		line(xt2,yt2,xt1,yt1);

		//—————显示发射角度盘————————
		int x0_l=92,y0_l=510;//之前量好的圆心坐标
		int xt_l,yt_l;//末位置的坐标
		int radium_l=80;//之前量好的半径

		if(combatData.tank[judge].tankDirection==1){				
			xt_l=(int)(x0_l+radium_l*(cos(combatData.tank[judge].tankCita+combatData.tank[judge].launchCita)));
			yt_l=(int)(y0_l-radium_l*(sin(combatData.tank[judge].tankCita+combatData.tank[judge].launchCita)));
		}
		else{
			xt_l=(int)(x0_l-radium_l*(cos(combatData.tank[judge].tankCita+combatData.tank[judge].launchCita)));
			yt_l=(int)(y0_l-radium_l*(sin(combatData.tank[judge].tankCita+combatData.tank[judge].launchCita)));
		}

		setcolor(RED);
		setlinestyle(PS_SOLID, NULL, 5);
		line(x0_l,y0_l,xt_l,yt_l);

		//—————————显示蓄力条————————————
		IMAGE power;
		power=power_temp;
		IMAGE background_p;//创建一个临时对象
		getimage(&background_p,219,575,500,15);//获取检验区域图像，准备去除
		DWORD* background_back=GetImageBuffer(&background_p);

		DWORD* power_M=GetImageBuffer(&power);
		for(int i=0;i<(5*combatData.tank[judge].launchStrength);i++){
			for(int j=0;j<15;j++){
				background_back[(j*500)+i]=power_M[(j*500)+i];
			}
		}

		putimage(219,575,&background_p);
		//——————————显示能量条————————————
		IMAGE energy;
		energy=energy_temp;
		IMAGE background_e;//创建一个临时对象
		getimage(&background_e,232,551,460,15);//获取检验区域图像，准备去除
		background_back=GetImageBuffer(&background_e);

		DWORD* energy_M=GetImageBuffer(&energy);
		for(int i=0;i<(5*combatData.tank[judge].energy);i++){
			for(int j=0;j<15;j++){
				background_back[(j*460)+i]=energy_M[(j*460)+i];
			}
		}

		putimage(232,551,&background_e);





	}
}

//```````````````````````````````````卡片面板````````````````````````````````````````
void CcombatShower::cardTransform(IMAGE &img,CardName cardname){//将卡片名信息与图形联系在一起
	if(cardname==BLINK)
		img=card_blink;
	else if(cardname==NUCLEAR)
		img=card_nuclear;
	else if(cardname==HEAL)
		img=card_cure;
	else if(cardname==GUIDE)
		img=card_guide;
	else if(cardname==BET)
		img=card_bet;
	else if(cardname==SX)
		img=card_sx;
	else if(cardname==LUNAHEAL)
		img=card_lunaheal;
	else if(cardname==RELOAD)
		img=card_reload;
	else if(cardname==CRITSPACE)
		img=card_critspace;
	else if(cardname==CARDSWEEP)
		img=card_cardsweep;
	else if(cardname==THUNDERSTORM)
		img=card_thunderstorm;
	else if(cardname==BARRIER)
		img=card_barrier;

	else
		img=card_unknown;
}

void CcombatShower::showCardPanel(const CcombatData &combatData){
	//————————显示卡片面板————————
	eliminateBoundary(cardpanel,937,0,63,313);
	putimage(937,0,&cardpanel);
	
	//————————显示各玩家手牌——————
	int judge=combatData.whoIsPlaying;
	if(judge>=0&&judge<=PLAYERNUM){
		IMAGE card1/*938,1*/,card2/*938,79*/,card3/*938,156*/,card4/*938,243*/;
		for(int i=1;i<5;i++){
			if(combatData.tank[judge].myCards[i]!=NULL){
				IMAGE card_temp;
			cardTransform(card_temp,combatData.tank[judge].myCards[i]->cardName);
				putimage(938,1+(i-1)*80,&card_temp);

			}
			if(combatData.tank[judge].cardUsingIndex==i){
				IMAGE light;
				light=card_light;
				eliminateBoundary(light,938,1+(i-1)*80,63,79);
				putimage(938,1+(i-1)*80,&light);
			}


		}


	}
	//————————————————显示牌堆剩余————————————————
		IMAGE card_left;
		card_left=card_left_temp;
		eliminateBoundary(card_left,800,10,88,19);
		putimage(800,10,&card_left);
		numChangeImage(combatData.cardBox.cardTotalLeftNum,888,6);
		
}




//```````````````````````````````````信息面板````````````````````````````````````````
void CcombatShower::showInfo(const CcombatData &combatData){
	setcolor(WHITE);


	//————————坦克信息——————————
	for(int i=0;i<PLAYERNUM;i++){
		//——————名字————————
		char name[20]="Player";
		char nnNum[20];
		sprintf(nnNum, "%d", i+1);
		strcat(name,nnNum);
		outtextxy(100+i*200,50, name);

		//———————生命—————————
		char life[20]="生命:";
		char lNum[20];
		sprintf(lNum, "%d", (int)combatData.tank[i].hp);
		strcat(life,lNum);
		outtextxy(100+i*200,75,life);


		//———————力量————————
		char stren[20]="力量:";
		char sNum[20];
		sprintf(sNum, "%d",(int) combatData.tank[i].launchStrength);
		strcat(stren,sNum);
		outtextxy(100+i*200,100, stren);
		//———————launch角度—————————
		char lcite[25]="launch角度:";
		char lcNum[25];
		sprintf(lcNum, "%f", combatData.tank[i].launchCita);
		strcat(lcite,lcNum);
		outtextxy(100+i*200,125, lcite);
		//———————tank角度—————————
		char tcite[25]="tank角度:";
		char tcNum[25];
		sprintf(tcNum, "%f", combatData.tank[i].tankCita);
		strcat(tcite,tcNum);
		outtextxy(100+i*200,150, tcite);
		//———————能量————————
		char energy[20]="能量:";
		char eNum[20];
		sprintf(eNum, "%d",(int) combatData.tank[i].energy);
		strcat(energy,eNum);
		outtextxy(100+i*200,175, energy);
	}




}

//-------------------------------以下是地图生动小动画 依旧是静态 但是用static 独立数据来完成绘图----------------------------------
void CcombatShower::flashPlayer(const CcombatData &combatData){
	IMAGE flashplayer_r;
	flashplayer_r=flashplayer;
	int judge=combatData.whoIsPlaying;
	if(judge>=0&&judge<=PLAYERNUM){
		if((int)(combatData.tank[combatData.whoIsPlaying].timer)%2==0)
		{
			int real_tx=(int)(combatData.tank[combatData.whoIsPlaying].position.x-((combatData.tank[combatData.whoIsPlaying].tkWidth*ROT_CONST)/2));//坐标转换过后的坦克x坐标
			int real_ty=37+(int)((BFHEIGHT-combatData.tank[combatData.whoIsPlaying].position.y)-(combatData.tank[combatData.whoIsPlaying].tkHeight*ROT_CONST));//坐标转换过后的坦克y坐标
			eliminateBoundary(flashplayer_r,real_tx+10,real_ty-55,50,50);
			putimage(real_tx+10,real_ty-55,&flashplayer_r);
		}
	}


}
void CcombatShower::flyBird(){
	static int bird_x=2,bird_y=100;
	bird_x+=5;
	IMAGE bird;
	bird=bird_temp;
	eliminateBoundary(bird,bird_x,bird_y,25,25);
	putimage(bird_x,bird_y,&bird);
	//numChangeImage(123,100,100);
	if(bird_x>=999)
		bird_x=2;

}


//-------------------------------以下是游戏流程游戏状态一类的谁赢了 谁输了xxx的----------------------------------
void CcombatShower::nextPlayer(const CcombatData &combatData){
	IMAGE next;
	next=next_temp;
	if(combatData.combatState==PLAYER_START_STAGE){//数据不对 无法持续显示

		eliminateBoundary(next,0,0,1000,600);
		putimage(0,0,&next);

	}
}

void CcombatShower::end_Cartoon(const CcombatData &combatData)
{	
	closegraph();
	initgraph(640,480);
	// 获得窗口句柄
	HWND hWnd = GetHWnd();
	// 使用 API 函数修改窗口名称
	SetWindowText(hWnd, "感谢试玩！【疯狂坦克DIY】 Made by SAT");

	static int x,y;
	static double v,Cita;
    IMAGE img1, img2,img3,img4;
	loadimage(&img1, _T("res\\picture\\endCartoon\\rotate.jpg"),600,400);//旋转图像
    loadimage(&img3,"res\\picture\\endCartoon\\background.jpg",640,480);
	if(Cita<2*PI)
	{
		
		for(;Cita<2*PI;Cita+=0.1*PI)
		{// 旋转图像 30 度 (PI / 6)
			rotateimage(&img2, &img1,Cita);
			img4=img2;
			BeginBatchDraw();   
			// 显示旋转后的图像
			putimage(0,0,&img3);
			eliminateBoundary(img4,50,50,600,400);
			putimage(50, 50, &img4);
			FlushBatchDraw();
			Sleep(10);
			cleardevice();
		}	
	}
	else Sleep(30);
	//while(1)
	//{
	//	circle(x,y,20);	
	//	for(int i=0;i<100;i++)
	//	{
	//		srand( (unsigned)time( NULL )+y-100);
	//		x=rand()%1000;
	//		y=rand()%600;
	//		v= ((rand() % 250) / 100.0 + 1);	
	//		// 计算新位置
	//		x+=v;
	//		putimage(0,0,&img3);
	//		circle(x,y,5);
	//		if(getch())
	//			break;	
	//	}
	//}
	system("pause");
}

