#include<stdio.h>
#include<graphics.h>  //easyxͼ�ο�ͷ�ļ�
#include<time.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


#define WIN_SIZE 500               //���ڴ�С
#define WIN_HALF (WIN_SIZE/2)      //���ڵ�һ��


IMAGE spaceMan[59];//̫����ͼƬ����
IMAGE Other[6];   //�����ϵ�����ͼƬ��ɵ�����

void loadImg()     //����ͼƬ�ĺ���
{
	char fileName[50] = {0};
	for (int i=0;i<59;i++)
	{
		sprintf_s(fileName,"./images/human (%d).jpg",i+2);
		loadimage(spaceMan+i, fileName, 140, 130);//����ͼƬ,ͼƬ�±�Ϊ2��60
	}
}


//̫���˶���Ч��
void animation()
{
	static DWORD t1 = 0;//ֻ��ʼ��һ��
	DWORD t2 = clock();//��ȡ�������е����øú����������ĺ�����
	//��ͼƬ�����������
	static int i = 0;
	//Sleep(20);             //�ó������ߣ������������ӳ٣�����ֻ���ö����仯��һ��,��ʱ������
	if (t2-t1>20)
	{
		i = (i + 1) % 59;
		t1 = t2;
	}
	putimage(WIN_HALF-70, WIN_HALF-50, spaceMan + i);
	
}

void setTextStyle(int h,int w,const char *faceName)
{
	LOGFONT f = { 0 };//��ʼ���ṹ��
	f.lfHeight = h;
	f.lfWidth = w;
	strcpy_s(f.lfFaceName, faceName);
	settextstyle(&f);
}

//�����������
void gameDraw()
{
	setbkcolor(RGB(223, 230, 240));  //����������ɫ��ʹ����ԭɫ�Ĳ�������
	cleardevice();                //��ʹ��������ɫҲ��ʾ����������Ϊԭ��ɫͼ����һ���ɫ��ʹ�������䡪����ջ�ͼ�豸
	setbkmode(TRANSPARENT);      //���ñ���͸��
	//���Ʊ��̣�������ֵ���һȦ���ɸ����Լ���ϲ�ø��ģ�
	setlinecolor(RGB(176 ,148,149));
	setlinestyle(PS_SOLID,40);
	setfillcolor(RGB(223, 230, 240));
	fillellipse(0,0, WIN_SIZE, WIN_SIZE);
	//��������
	setlinecolor(BLUE);
	setlinestyle(PS_SOLID, 2);

	//����
	line(WIN_HALF - 30,22, WIN_HALF - 30, 130);
	line(WIN_HALF +80, WIN_HALF +120, WIN_HALF + 80, WIN_HALF +170);
	line(WIN_HALF - 50, WIN_HALF +170, WIN_HALF -50, WIN_HALF +225);
	//2������
	line(WIN_HALF - 195, WIN_HALF-120, WIN_HALF +195, WIN_HALF - 120);
	line(WIN_HALF - 195, WIN_HALF +120, WIN_HALF + 195, WIN_HALF +120);
	line(WIN_HALF -50, WIN_HALF +170, WIN_HALF +80, WIN_HALF + 170);

	//������˯�ߡ����߾������ʾ�����Ǽٵģ���Ϊ�����漶û����Ӧ�Ĵ���������ȡ���ݣ�
	settextcolor(BLACK);
	setTextStyle(35,13,"Arial");//���øÿ��������ʽ
	outtextxy(100,90,"90%");    
	outtextxy(110, WIN_HALF+130, "˯��");
	outtextxy(WIN_HALF-50, WIN_HALF + 130, "7h30min");
	outtextxy(WIN_HALF +100, WIN_HALF + 130, "����");
	outtextxy(WIN_HALF - 30, WIN_HALF + 180, "2.78km");

	//������ʾ��Ҳ�Ǽٵģ�
	settextcolor(RED);
	setTextStyle(23, 9, "Arial");
	outtextxy(75, WIN_HALF + 58, "64-110");
	settextcolor(RED);
	setTextStyle(25, 10, "Arial");	
	outtextxy(123, WIN_HALF + 90, "67");

	//������ʾ��ĿǰҲ�Ǽٵģ�����δ�����ܸ��º�Windows������ͬ�������ڴ���
	settextcolor(RGB(133,185,82));
	setTextStyle(25, 10, "Arial");
	outtextxy(WIN_HALF - 15, 40, "��������");
	settextcolor(RGB(133, 185, 82));
	setTextStyle(15, 10, "Arial");
	outtextxy(WIN_HALF - 15, 73, "���� 26��");
	outtextxy(WIN_HALF - 15, 94, "22��  16��");

	//������ʾ���ٵģ�
	settextcolor(BLACK);
	setTextStyle(25, 10, "Arial");
	outtextxy(WIN_HALF + 130, WIN_HALF +90, "10098");


	//��ʾ��̬ʱ��
	//��ȡ��ǰ��ϵͳʱ��
	time_t curTime = time(NULL);
	//printf("%lld\n",curTime);//���������������ʱ���룬���ҿ�����
	 struct tm * humanTime=localtime(&curTime);
	/* printf_s("��%d %d-%d %d:%d:%d\n",humanTime->tm_wday, humanTime->tm_mon+1, humanTime->tm_mday, humanTime->tm_hour, humanTime->tm_min, humanTime->tm_sec);*/
	 char buf[40] = { 0 };
	 settextcolor(BLACK);
	 setTextStyle(70,28,"Arial");//�������ʱ�ֵ�������ʽ
	 sprintf_s(buf,"%2d:%2d", humanTime->tm_hour, humanTime->tm_min);
	 outtextxy(WIN_HALF-80, WIN_HALF-115, buf);
	 settextcolor(BLACK);
	 setTextStyle(20, 12, "Arial");//����������������ʽ
	 sprintf_s(buf, "%2d", humanTime->tm_sec);
	 outtextxy(335, 175, buf);

	 settextcolor(BLACK);
	 setTextStyle(25, 10, "Arial");//����������ں����ڵ�������ʽ
	 //sprintf_s(buf, "%d", humanTime->tm_wday);
	 strftime(buf,40,"%A", humanTime);//ʹ��C�����Դ���ʱ���ʽת����ʾ���ڼ�
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
//}����е����⣬��û��ʵ��

int main()
{ 
	//����ͼ�ʹ���
	initgraph(500, 500,EW_SHOWCONSOLE);
	// printf_s("hellow world");//���������̨������easyx��������ʱ�����������Ѿ���������
	//�����ı���ʽ
	//settextcolor(BLACK);
	//setTextStyle(55, 23, "Arial");//�Լ����õĵ����ı���ʽ�ĺ���
	//outtextxy(50,50,"90%");
	loadImg();

	BeginBatchDraw();//˫�����ͼ�����˸����
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

