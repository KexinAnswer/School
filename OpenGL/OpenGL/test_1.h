#pragma once

#if 0
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void init(void)//窗口的创建
{
	glClearColor(1.0, 1.0, 1.0, 0.0); //三个1.0是白色背景,三个0.0是黑色背景
	glColor3f(1.0, 0.0, 0.0); //红线
	gluOrtho2D(0.0, 300.0, 0.0, 500.0);//在窗口内建立二维直角坐标系

}

void dda_line(int xa, int ya, int xb, int yb)//编写dda算法
{
	float delta_x, delta_y, x, y;
	int dx, dy, steps;//定义变量
	dx = xb - xa;
	dy = yb - ya;
	if (abs(dx) > abs(dy))//斜率小于1则以单位x间隔取样,逐个计算每一个y值
		steps = abs(dx);
	else//斜率大于1则以y为间隔取样,逐个计算每一个y值
		steps = abs(dy);
	delta_x = (GLfloat)dx / (GLfloat)steps;//通过两个单位长度的计算来代替斜率
	delta_y = (GLfloat)dy / (GLfloat)steps;
	x = xa;
	y = ya;
	glClear(GL_COLOR_BUFFER_BIT);
	for (int k = 1; k <= steps; k++)
	{
		x += delta_x;
		y += delta_y;
		glBegin(GL_POINTS);//画点函数,只有两个参数,
		glVertex2f(x, y);//根据x,y进行划线
		glEnd();
	}

}



void display(void)//创建一个没有参数的函数来调用上一个函数
{
	glClear(GL_COLOR_BUFFER_BIT); //刷新缓存,在窗口中出现
	dda_line(0, 0, 500, 500);//dda函数的调用
	glFlush();//清理缓存来处理函数
}

void Test1(int* argc, char** argv)
{
	glutInit(argc, argv);//glut的初始化
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);//窗口的大小500x500
	glutInitWindowPosition(0, 0);//定义窗口的位置,在屏幕向左边0像素,屏幕上面向下0像素
	glutCreateWindow("DDA算法的实现");//屏幕上方显示的内容
	init();//调用上面的init函数
	glutDisplayFunc(display);//在窗口中显示diaplay
	glutMainLoop();

}

#endif

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <graphics.h>
#include <conio.h>
//#include<GL/GL.H>
//#include<gl/glu.h>


//using namespace std;

void MidPLine(int x1, int y1, int x2, int y2) {
	int x, y, d0, d1, d2, a, b;
	y = y1;
	a = y1 - y2;
	b = x2 - x1;
	d0 = 2 * a + b;
	d1 = 2 * a;
	d2 = 2 * (a + b);
	for (x = x1; x <= x2; x++) {
		putpixel(x, y, 255);
		if (d0 < 0) {
			y++;
			d0 += d2;
		}
		else {
			d0 += d1;
		}
	}
}

void Test1() {
	initgraph(680, 480);
	MidPLine(300, 100, 400, 400);
	_getch();
	closegraph();
	system("pause");
}