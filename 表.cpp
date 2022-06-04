#include<graphics.h>
#include <stdio.h>
#include <mmsystem.h>
#include "date_tool.h"
#pragma comment (lib,"winmm.lib")
IMAGE img[71];
IMAGE sz[11];
IMAGE sz2[10];
void drawTime() {
	//基础版
	//获取时间，麻烦又常用，分装起来
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
	//去掉窗口的标题栏
	//找到这个窗口
	HWND hwnd = GetHWnd();//获取当前窗口的窗口句柄
	SetWindowLong(
		hwnd,
		GWL_STYLE,	//要设置窗口的方格
		GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	//设置窗口为顶层窗口，同时设置位置和大小
	SetWindowPos(
		hwnd,//设置哪个窗口
		HWND_TOPMOST,//顶层窗口
		0, 0,//窗口的位置
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		SWP_SHOWWINDOW);
	//设置窗口为透明效果
	//要求想把窗口设置为分层窗口
	SetWindowLong(hwnd,
		GWL_EXSTYLE,
		GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	//设置分层窗口的透明度
	SetLayeredWindowAttributes(
		hwnd,
		RGB(0, 0, 0),//指定需要变成透明的背景色
		0,//透明度，0::去昂透明 255:完全不透明
		LWA_COLORKEY);
	//马上开发价值6000+万的项目
	//准备工作,亲历窗口
	setbkcolor(RGB(0, 0, 0));
	cleardevice();//使用背景颜色清理窗口
	//设置坐标原点
	setorigin(GetSystemMetrics(SM_CXSCREEN) - 100, 100);
	//绘制表盘
	//没有美工基础，能不能独立做项目
	//淘宝美工-非常便宜-<100元
	IMAGE bg;
	loadimage(&bg,
		"1.png",//图片文件名
		200, 200,//显示要显示的高度和宽度
		true);
	putimage(-100, -100, &bg);//显示图片
	//话一个黑色圆圈，去除毛刺。
	setlinecolor(BLACK);
	setlinecolor(BROWN);
	setlinestyle(PS_SOLID, 8);
	circle(0, 0, 99);
	circle(0, 0, 102);
	//画太空人
	//难道就没看过周杰伦关于篮球的电影(大灌篮)
	//预加载太空人图片
	char imgName[64];
	for (int i = 0; i < 71; i++)
	{
		//human _0000_图层 71
		sprintf_s(imgName, sizeof(imgName),
			"img/human_%04d_图层 %d.jpg", i, 71 - i);
		loadimage(&img[i], imgName, 50, 50, true);
	}
	//预加载数字图片
	for (int i = 0; i < 10; i++) {
		sprintf_s(imgName, sizeof(imgName), "img/%d.jpg", i);
		loadimage(&sz[i], imgName, 12, 17, true);
		loadimage(&sz2[i], imgName, 10, 10, true);
	}
	loadimage(&sz[10], "img/rect.jpg", 3, 3, true);
	mciSendString("Play 三号线.mp3 repeat", 0, 0, 0);
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