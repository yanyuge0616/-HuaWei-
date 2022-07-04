#include<stdio.h>
#include<time.h>
#include"tools.hpp"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
/*
	1,�ı���������
	2,ͼƬ����Ч��
	3,���Ʊ���
*/
#define WIN_SIZE 500
#define WIN_HALF (WIN_SIZE/2)	//���ڵ�һ��
IMAGE spaceMan[59];
IMAGE other[6];
const char *week[7] = {"��","һ","��","��","��","��","��" };
void setTextStyle(int height,int width,const char *faceName)
{
	LOGFONT f = { 0 };
	f.lfHeight = height;
	f.lfWidth = width;
	f.lfQuality = ANTIALIASED_QUALITY;
	strcpy(f.lfFaceName, faceName);
	settextstyle(&f);
}
void loadImg()
{
	mciSendString("open ./images/�����.mp3", NULL, 0, NULL);
	mciSendString("play ./images/�����.mp3 repeat", NULL, 0, NULL);

	char fileName[50] = { 0 };
	for (int i = 0; i < 59; i++)
	{
		sprintf_s(fileName,"./images/human (%d).jpg", i+2);
		loadimage(spaceMan + i,fileName , 140, 130);
	}
	loadimage(other + 0, "./images/other1.png", 70, 70);
	loadimage(other + 1, "./images/other2.png", 60, 60);
	loadimage(other + 2, "./images/other3.png", 55, 55);
	loadimage(other + 3, "./images/other4.png", 30, 30);
	loadimage(other + 4, "./images/other5.png", 30, 30);
	loadimage(other + 5, "./images/other6.png", 60, 60);
}
//̫������ת����
void animation()
{
	static int index = 0;	//[0~59)
	putimage(175, 210, spaceMan+index);

	static DWORD t1;
	DWORD t2 = clock();
	if (t2 - t1 > 20)
	{
		index = (index + 1) % 59;
		t1 = t2;
	}
}
void gameDraw()
{
	
	setbkcolor(RGB(223, 230, 240));
	cleardevice();
	//���Ʊ���
	setlinecolor(RGB(68, 68, 68));
	setlinestyle(PS_SOLID, 40);
	setfillcolor(RGB(223, 230, 240));
	fillellipse(0, 0, WIN_SIZE, WIN_SIZE);
	
	//��������
	setlinestyle(PS_SOLID, 4);
	setlinecolor(BLACK);
	//����������
	line(WIN_HALF - 30, 20, WIN_HALF - 30, 130);
	//����x2
	line(WIN_HALF - 195, WIN_HALF - 120, WIN_HALF + 195, WIN_HALF - 120);
	line(WIN_HALF - 195, WIN_HALF + 120, WIN_HALF + 195, WIN_HALF + 120);
	//��������x3
	line(WIN_HALF + 80, WIN_HALF + 120, WIN_HALF + 80, WIN_HALF + 175);
	line(WIN_HALF + 80, WIN_HALF + 175, WIN_HALF - 60, WIN_HALF + 175);
	line(WIN_HALF - 60, WIN_HALF + 175, WIN_HALF - 60, WIN_HALF + 175 + 48);


	setbkmode(TRANSPARENT);
	//���Ͽ���ʪ��90%
	setTextStyle(55, 23, "Arial");
	settextcolor(BLACK);
	outtextxy(WIN_HALF - 155, 75, "90%");
	drawImg(other + 5, WIN_HALF - 90, 35);	//���
	//����
	setTextStyle(25, 15, "����");
	outtextxy(WIN_HALF - 25, 35, "��������");

	setTextStyle(25, 13, "����");
	outtextxy(WIN_HALF - 25, 65, "����");
	outtextxy(WIN_HALF - 25, 95, "25��");
	outtextxy(WIN_HALF + 38, 65, "26��");
	outtextxy(WIN_HALF + 38, 95, "17��");
	drawImg(other+4, WIN_HALF + 73, 60);	//����ļ�ͷ
	drawImg(other+3, WIN_HALF + 73, 90);	//����ļ�ͷ
	drawImg(other+1, WIN_HALF + 105, 70);	//̫��

	// �²���
	setTextStyle(37, 17, "����");
	outtextxy(100, WIN_HALF + 130, "˯��");
	outtextxy(WIN_HALF + 90, WIN_HALF + 130, "����");

	setTextStyle(40, 15, "Arial");
	outtextxy(185, WIN_HALF + 125, "7h30m");
	outtextxy(215, WIN_HALF + 180, "9.88km");

	//�м�
	//����
	setTextStyle(25, 13, "����");
	outtextxy(60, WIN_HALF + 30, "80~128");
	drawImg(&other[0], 65, WIN_HALF + 50);	//����ͼ

	setTextStyle(40, 15, "Arial");
	outtextxy(135, WIN_HALF + 60, "92");
	// ����
	drawImg(&other[2], WIN_HALF + 65, WIN_HALF + 65);
	outtextxy(WIN_HALF + 125, WIN_HALF + 75, "9527");
	
	//ʱ�䡢�������
	time_t timep = time(NULL);			//��ȡ��ǰʱ��
	struct tm* p = localtime(&timep);	//��ʱ��ת�ɸ�ʽ��ʱ��

	setTextStyle(25, 12, "����");
	outtextxy(WIN_HALF + 110, WIN_HALF - 20, "������ʮһ");
	char fileName[40] = { 0 };
	sprintf_s(fileName, "��%s %d-%d", week[p->tm_wday], p->tm_mon + 1, p->tm_mday);
	outtextxy(WIN_HALF + 110, WIN_HALF + 10, fileName);

	// ��ȡ����
	setTextStyle(100, 40, "Arial");
	char szBuf[40] = { 0 };
	sprintf_s(szBuf, "%d:%02d", p->tm_hour, p->tm_min);
	outtextxy(105, 120, szBuf);
	// ��
	setTextStyle(55, 23, "Arial");
	sprintf(szBuf, "%02d", p->tm_sec);
	outtextxy(335, 160, szBuf);
}
int main()
{
	initgraph(WIN_SIZE, WIN_SIZE/*,EW_SHOWCONSOLE*/);
	SetWindowNewStyle(WIN_SIZE, WIN_SIZE);


	loadImg();

	BeginBatchDraw();	//˫����
	while (true)
	{
		gameDraw();
		animation();

		mouseEvent();

		FlushBatchDraw();
	}
	EndBatchDraw();
	return 0;
}