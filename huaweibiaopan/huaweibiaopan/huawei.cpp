#include<stdio.h>
#include<graphics.h>  //easyx图形库头文件
#include<time.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


#define WIN_SIZE 500               //窗口大小
#define WIN_HALF (WIN_SIZE/2)      //窗口的一半


IMAGE spaceMan[59];//太空人图片数组
IMAGE Other[6];   //表盘上的其他图片组成的数组

void loadImg()     //加载图片的函数
{
	char fileName[50] = {0};
	for (int i=0;i<59;i++)
	{
		sprintf_s(fileName,"./images/human (%d).jpg",i+2);
		loadimage(spaceMan+i, fileName, 140, 130);//加载图片,图片下标为2到60
	}
}


//太空人动画效果
void animation()
{
	static DWORD t1 = 0;//只初始化一次
	DWORD t2 = clock();//获取程序运行到调用该函数所经过的毫秒数
	//把图片输出到窗口上
	static int i = 0;
	//Sleep(20);             //让程序休眠，让整个程序都延迟，但我只想让动画变化慢一点,此时不能用
	if (t2-t1>20)
	{
		i = (i + 1) % 59;
		t1 = t2;
	}
	putimage(WIN_HALF-70, WIN_HALF-50, spaceMan + i);
	
}

void setTextStyle(int h,int w,const char *faceName)
{
	LOGFONT f = { 0 };//初始化结构体
	f.lfHeight = h;
	f.lfWidth = w;
	strcpy_s(f.lfFaceName, faceName);
	settextstyle(&f);
}

//其他界面绘制
void gameDraw()
{
	setbkcolor(RGB(223, 230, 240));  //调整背景颜色，使用三原色的参数设置
	cleardevice();                //即使设置了颜色也显示不出来，因为原来色图上有一层黑色，使用这个语句——清空绘图设备
	setbkmode(TRANSPARENT);      //设置背景透明
	//绘制表盘（外面最粗的那一圈，可根据自己的喜好更改）
	setlinecolor(RGB(176 ,148,149));
	setlinestyle(PS_SOLID,40);
	setfillcolor(RGB(223, 230, 240));
	fillellipse(0,0, WIN_SIZE, WIN_SIZE);
	//绘制线条
	setlinecolor(BLUE);
	setlinestyle(PS_SOLID, 2);

	//竖线
	line(WIN_HALF - 30,22, WIN_HALF - 30, 130);
	line(WIN_HALF +80, WIN_HALF +120, WIN_HALF + 80, WIN_HALF +170);
	line(WIN_HALF - 50, WIN_HALF +170, WIN_HALF -50, WIN_HALF +225);
	//2条横线
	line(WIN_HALF - 195, WIN_HALF-120, WIN_HALF +195, WIN_HALF - 120);
	line(WIN_HALF - 195, WIN_HALF +120, WIN_HALF + 195, WIN_HALF +120);
	line(WIN_HALF -50, WIN_HALF +170, WIN_HALF +80, WIN_HALF + 170);

	//电量、睡眠、行走距离的显示（这是假的，因为在桌面级没有相应的传感器来获取数据）
	settextcolor(BLACK);
	setTextStyle(35,13,"Arial");//设置该块字体的样式
	outtextxy(100,90,"90%");    
	outtextxy(110, WIN_HALF+130, "睡眠");
	outtextxy(WIN_HALF-50, WIN_HALF + 130, "7h30min");
	outtextxy(WIN_HALF +100, WIN_HALF + 130, "距离");
	outtextxy(WIN_HALF - 30, WIN_HALF + 180, "2.78km");

	//心率显示（也是假的）
	settextcolor(RED);
	setTextStyle(23, 9, "Arial");
	outtextxy(75, WIN_HALF + 58, "64-110");
	settextcolor(RED);
	setTextStyle(25, 10, "Arial");	
	outtextxy(123, WIN_HALF + 90, "67");

	//天气显示（目前也是假的，不过未来可能更新和Windows天气相同，敬请期待）
	settextcolor(RGB(133,185,82));
	setTextStyle(25, 10, "Arial");
	outtextxy(WIN_HALF - 15, 40, "天气优质");
	settextcolor(RGB(133, 185, 82));
	setTextStyle(15, 10, "Arial");
	outtextxy(WIN_HALF - 15, 73, "晴天 26°");
	outtextxy(WIN_HALF - 15, 94, "22°  16°");

	//步数显示（假的）
	settextcolor(BLACK);
	setTextStyle(25, 10, "Arial");
	outtextxy(WIN_HALF + 130, WIN_HALF +90, "10098");


	//显示动态时间
	//获取当前的系统时间
	time_t curTime = time(NULL);
	//printf("%lld\n",curTime);//里面包含了年月日时分秒，并且看不懂
	 struct tm * humanTime=localtime(&curTime);
	/* printf_s("周%d %d-%d %d:%d:%d\n",humanTime->tm_wday, humanTime->tm_mon+1, humanTime->tm_mday, humanTime->tm_hour, humanTime->tm_min, humanTime->tm_sec);*/
	 char buf[40] = { 0 };
	 settextcolor(BLACK);
	 setTextStyle(70,28,"Arial");//设置输出时分的文字样式
	 sprintf_s(buf,"%2d:%2d", humanTime->tm_hour, humanTime->tm_min);
	 outtextxy(WIN_HALF-80, WIN_HALF-115, buf);
	 settextcolor(BLACK);
	 setTextStyle(20, 12, "Arial");//设置输出秒的文字样式
	 sprintf_s(buf, "%2d", humanTime->tm_sec);
	 outtextxy(335, 175, buf);

	 settextcolor(BLACK);
	 setTextStyle(25, 10, "Arial");//设置输出星期和日期的文字样式
	 //sprintf_s(buf, "%d", humanTime->tm_wday);
	 strftime(buf,40,"%A", humanTime);//使用C语言自带的时间格式转换显示星期几
	 outtextxy(WIN_HALF + 122, WIN_HALF - 20, buf);
	 sprintf_s(buf, "%d-%d", humanTime->tm_mon+1, humanTime->tm_mday);
	 outtextxy(WIN_HALF + 140, WIN_HALF, buf);
}

void smallpic()
{
	loadimage(Other,"./images/other6.png",45,45);
	putimage(165, 50, Other,SRCPAINT);
	loadimage(Other, "./images/other2.png", 45, 45);
	putimage(WIN_HALF+100, 66, Other, SRCPAINT);
	loadimage(Other, "./images/other1.png", 40, 40);
	putimage(75, WIN_HALF +80, Other, SRCPAINT);
	loadimage(Other, "./images/other3.png", 44, 44);
	putimage(WIN_HALF + 80, WIN_HALF + 80, Other, SRCPAINT);
	loadimage(Other, "./images/other5.png", 20, 20);
	putimage(WIN_HALF + 60, 70, Other, SRCPAINT);
	loadimage(Other, "./images/other4.png", 20, 20);
	putimage(WIN_HALF + 60, 91, Other, SRCPAINT);
}

//void musicplay()
//{
//	mciSendString(_T("open .\images\weiwu.mp3 alias mymusic"), NULL, 0, NULL);
//	mciSendString(_T("play mymusic repeat"), NULL, 0, NULL);
//
//}这边有点问题，我没有实现

int main()
{ 
	//创建图型窗口
	initgraph(500, 500,EW_SHOWCONSOLE);
	// printf_s("hellow world");//输出到控制台，当用easyx创建窗口时这个输出函数已经不适用了
	//设置文本样式
	//settextcolor(BLACK);
	//setTextStyle(55, 23, "Arial");//自己设置的调整文本格式的函数
	//outtextxy(50,50,"90%");
	loadImg();

	BeginBatchDraw();//双缓冲绘图解决闪烁问题
	while (true)
	{
		gameDraw();
		animation();
		smallpic();
		//musicplay();
		FlushBatchDraw();
	}
	return 0;
}

