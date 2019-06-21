#pragma once

#if 0
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void init(void)//���ڵĴ���
{
	glClearColor(1.0, 1.0, 1.0, 0.0); //����1.0�ǰ�ɫ����,����0.0�Ǻ�ɫ����
	glColor3f(1.0, 0.0, 0.0); //����
	gluOrtho2D(0.0, 300.0, 0.0, 500.0);//�ڴ����ڽ�����άֱ������ϵ

}

void dda_line(int xa, int ya, int xb, int yb)//��дdda�㷨
{
	float delta_x, delta_y, x, y;
	int dx, dy, steps;//�������
	dx = xb - xa;
	dy = yb - ya;
	if (abs(dx) > abs(dy))//б��С��1���Ե�λx���ȡ��,�������ÿһ��yֵ
		steps = abs(dx);
	else//б�ʴ���1����yΪ���ȡ��,�������ÿһ��yֵ
		steps = abs(dy);
	delta_x = (GLfloat)dx / (GLfloat)steps;//ͨ��������λ���ȵļ���������б��
	delta_y = (GLfloat)dy / (GLfloat)steps;
	x = xa;
	y = ya;
	glClear(GL_COLOR_BUFFER_BIT);
	for (int k = 1; k <= steps; k++)
	{
		x += delta_x;
		y += delta_y;
		glBegin(GL_POINTS);//���㺯��,ֻ����������,
		glVertex2f(x, y);//����x,y���л���
		glEnd();
	}

}



void display(void)//����һ��û�в����ĺ�����������һ������
{
	glClear(GL_COLOR_BUFFER_BIT); //ˢ�»���,�ڴ����г���
	dda_line(0, 0, 500, 500);//dda�����ĵ���
	glFlush();//��������������
}

void Test1(int* argc, char** argv)
{
	glutInit(argc, argv);//glut�ĳ�ʼ��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);//���ڵĴ�С500x500
	glutInitWindowPosition(0, 0);//���崰�ڵ�λ��,����Ļ�����0����,��Ļ��������0����
	glutCreateWindow("DDA�㷨��ʵ��");//��Ļ�Ϸ���ʾ������
	init();//���������init����
	glutDisplayFunc(display);//�ڴ�������ʾdiaplay
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