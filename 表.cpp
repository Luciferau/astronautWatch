#include<graphics.h>
#include <stdio.h>
#include <mmsystem.h>
#include "date_tool.h"
#pragma comment (lib,"winmm.lib")
IMAGE img[71];
IMAGE sz[11];
IMAGE sz2[10];
void drawTime() {
	//������
	//��ȡʱ�䣬�鷳�ֳ��ã���װ����
	int hour, minute, second;
	getTime(&hour, &minute, &second);
	//22:02:35
	int h1 = hour / 10;//22/10=2
	int h2 = hour % 10;//22%10=2
	putimage(-70, -40, &sz[h1]);
	putimage(-50, -40, &sz[h2]);

	putimage(-35, -37, &sz[10]);
	putimage(-35, -30, &sz[10]);

	int m1 = minute / 10;
	int m2 = minute % 10;
	putimage(-30, -40, &sz[m1]);
	putimage(-15, -40, &sz[m2]);

	putimage(10, -30, &sz2[second / 10]);
	putimage(25, -30, &sz2[second % 10]);
}
int main(void)
{
	initgraph(
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN));
	//ȥ�����ڵı�����
	//�ҵ��������
	HWND hwnd = GetHWnd();//��ȡ��ǰ���ڵĴ��ھ��
	SetWindowLong(
		hwnd,
		GWL_STYLE,	//Ҫ���ô��ڵķ���
		GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	//���ô���Ϊ���㴰�ڣ�ͬʱ����λ�úʹ�С
	SetWindowPos(
		hwnd,//�����ĸ�����
		HWND_TOPMOST,//���㴰��
		0, 0,//���ڵ�λ��
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		SWP_SHOWWINDOW);
	//���ô���Ϊ͸��Ч��
	//Ҫ����Ѵ�������Ϊ�ֲ㴰��
	SetWindowLong(hwnd,
		GWL_EXSTYLE,
		GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	//���÷ֲ㴰�ڵ�͸����
	SetLayeredWindowAttributes(
		hwnd,
		RGB(0, 0, 0),//ָ����Ҫ���͸���ı���ɫ
		0,//͸���ȣ�0::ȥ��͸�� 255:��ȫ��͸��
		LWA_COLORKEY);
	//���Ͽ�����ֵ6000+�����Ŀ
	//׼������,��������
	setbkcolor(RGB(0, 0, 0));
	cleardevice();//ʹ�ñ�����ɫ������
	//��������ԭ��
	setorigin(GetSystemMetrics(SM_CXSCREEN) - 100, 100);
	//���Ʊ���
	//û�������������ܲ��ܶ�������Ŀ
	//�Ա�����-�ǳ�����-<100Ԫ
	IMAGE bg;
	loadimage(&bg,
		"1.png",//ͼƬ�ļ���
		200, 200,//��ʾҪ��ʾ�ĸ߶ȺͿ��
		true);
	putimage(-100, -100, &bg);//��ʾͼƬ
	//��һ����ɫԲȦ��ȥ��ë�̡�
	setlinecolor(BLACK);
	setlinecolor(BROWN);
	setlinestyle(PS_SOLID, 8);
	circle(0, 0, 99);
	circle(0, 0, 102);
	//��̫����
	//�ѵ���û�����ܽ��׹�������ĵ�Ӱ(�����)
	//Ԥ����̫����ͼƬ
	char imgName[64];
	for (int i = 0; i < 71; i++)
	{
		//human _0000_ͼ�� 71
		sprintf_s(imgName, sizeof(imgName),
			"img/human_%04d_ͼ�� %d.jpg", i, 71 - i);
		loadimage(&img[i], imgName, 50, 50, true);
	}
	//Ԥ��������ͼƬ
	for (int i = 0; i < 10; i++) {
		sprintf_s(imgName, sizeof(imgName), "img/%d.jpg", i);
		loadimage(&sz[i], imgName, 12, 17, true);
		loadimage(&sz2[i], imgName, 10, 10, true);
	}
	loadimage(&sz[10], "img/rect.jpg", 3, 3, true);
	mciSendString("Play ������.mp3 repeat", 0, 0, 0);
	int k = 0;
	while (1)
	{
		putimage(-50, -15, &img[k]);
		k = (k + 1) % 71;//0..70..0..70
		Sleep(30);
		drawTime();
	}
	system("pause");
	return 0;
}