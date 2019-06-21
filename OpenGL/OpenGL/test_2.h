#pragma once
#include <cmath>
#include <stack>
#include "gl/glut.h"
#include "iostream"
using namespace std;

#define PI 3.14

struct Pos
{
	int x;
	int y;
	Pos(int mx, int my) :x(mx), y(my) {};
	Pos() :x(0), y(0) {};
};

stack<Pos> s;
int a[24][24] = { 0 };

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);//设置投影矩阵
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);//二维视景区域
	glPointSize(12.0f);
}
// 画棋子
void Drawtri(int x, int y, int color)
{
	double n = 200;//分段数
	float R = 10;//半径
	int i;
	if (color == 1)
	{
		glColor3f(1.0, 0.0, 0.0);
	}
	else if (color == 2)
	{
		glColor3f(0.0, 1.0, 0.0);
	}
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	for (i = 0; i <= n; i++)
		glVertex2f(R*cos(2 * PI / n * i) + x, R*sin(2 * PI / n * i) + y);
	glEnd();
	glPopMatrix();
}

// 绘制格线
void playMap()
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (int i = 0; i < 600; i += 25)
	{
		glVertex2f(i, 0);
		glVertex2f(i, 600);
	}
	for (int j = 0; j < 600; j += 25)
	{
		glVertex2f(0, j);
		glVertex2f(600, j);
	}
	glEnd();
	for (int k = 0; k < 24; k++)
	{
		for (int l = 0; l < 24; l++)
		{
			if (a[k][l] == 1)
			{
				Drawtri(k * 25 + 12, l * 25 + 12, 1);
			}
			else if (a[k][l] == 2)
			{
				Drawtri(k * 25 + 12, l * 25 + 12, 2);
			}
		}
	}
}

// 简单深度搜索填充 （四连通）
void DfsFill(int x, int y)
{
	if (x < 0 || y < 0 || x>23 || y>23)
	{
		return;
	}
	if (a[x][y] == 0)
	{
		a[x][y] = 2;
		DfsFill(x - 1, y);
		DfsFill(x + 1, y);
		DfsFill(x, y - 1);
		DfsFill(x, y + 1);
	}
}

// 扫描线种子填充算法（四连通）
void ScanFill(int x, int y)
{
	if (a[x][y] != 0)
	{
		return;
	}
	Pos first(x, y);
	s.push(first);
	while (!s.empty())
	{
		int rightX = 0;
		int leftX = 0;
		Pos cur = s.top();
		s.pop();
		a[cur.x][cur.y] = 2;
		// 遍历当前行
		for (int i = 1; i < 24; i++)
		{
			if (cur.x + i < 24)
			{
				if (a[cur.x + i][cur.y] == 0)
					a[cur.x + i][cur.y] = 2;
				else
				{
					rightX = cur.x + i - 1;
					break;
				}
			}
			if (i == 23)
			{
				rightX = 23;
			}
		}
		for (int i = 1; i < 24; i++)
		{
			if (cur.x - i > -1)
			{
				if (a[cur.x - i][cur.y] == 0)
					a[cur.x - i][cur.y] = 2;
				else
				{
					leftX = cur.x - i + 1;
					break;
				}
			}
			if (i == 0)
			{
				leftX = 0;
			}
		}

		cout << leftX << "," << rightX << endl;

		// 判断上行
		int upRightX = -1;
		for (int i = leftX; i <= rightX; i++)
		{
			if (a[i][cur.y + 1] == 0 && cur.y + 1 < 24)
			{
				upRightX = i;
			}
		}
		if (upRightX != -1)
		{
			Pos temPos(upRightX, cur.y + 1);
			s.push(temPos);
		}

		// 判断下行
		int downRightX = -1;
		for (int i = leftX; i <= rightX; i++)
		{
			if (a[i][cur.y - 1] == 0 && cur.y - 1 >= 0)
			{
				downRightX = i;
			}
		}
		if (downRightX != -1)
		{
			Pos temPos(downRightX, cur.y - 1);
			s.push(temPos);
		}

	}
}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	playMap();
	glFlush();
}


void mouse(GLint button, GLint action, GLint x, GLint y)
{
	int curX, curY;
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		curX = x / 25;
		curY = (600 - y) / 25;
		a[curX][curY] = 1;
		glutPostRedisplay();//重绘窗口
	}
	if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
	{
		curX = x / 25;
		curY = (600 - y) / 25;
		DfsFill(curX, curY);

		glutPostRedisplay();//重绘窗口
	}
}


void Test2(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("mouse");

	init();
	glutDisplayFunc(displayFcn);

	glutMouseFunc(mouse);

	glutMainLoop();

}