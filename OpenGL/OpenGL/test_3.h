#pragma once
#include "GL\glut.h"
#include <math.h>
#include <Windows.h>

//这是一个点的类，用于存储其中点的坐标
class Point
{
public:
	int x, y;
	void setxy(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

//点的数量
static int POINTSNUM = 0;

//用于存储点的集合,因为绘制的都是4个点的贝塞尔曲线，所以数组大小为4
static Point points[4];

//初始化函数
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0); //设定背景为黑色
	glColor3f(0.0, 0.0, 0.0); //绘图颜色为白色
	glPointSize(2.0); //设定点的大小为2*2像素的
	glMatrixMode(GL_PROJECTION); // 设定合适的矩阵
	glLoadIdentity(); // 是一个无参的无值函数，其功能是用一个4×4的单位矩阵来替换当前矩阵，实际上就是对当前矩阵进行初始化。也就是说，无论以前进行了多少次矩阵变换，在该命令执行后，当前矩阵均恢复成一个单位矩阵，即相当于没有进行任何矩阵变换状态
	gluOrtho2D(0.0, 600.0, 0.0, 480.0); //平行投影，四个参数分别是x,y范围
}

//绘制点
void setPoint(Point p) {
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
	glFlush();
}

// 绘制直线
void setline(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
	glFlush();
}

// 绘制贝塞尔曲线
Point setBezier(Point p1, Point p2, Point p3, Point p4, double t) {
	Point p;
	double a1 = pow((1 - t), 3);
	double a2 = pow((1 - t), 2) * 3 * t;
	double a3 = 3 * t*t*(1 - t);
	double a4 = t * t*t;
	p.x = a1 * p1.x + a2 * p2.x + a3 * p3.x + a4 * p4.x;
	p.y = a1 * p1.y + a2 * p2.y + a3 * p3.y + a4 * p4.y;
	return p;
}


//display函数
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}



// 鼠标事件
void mymouseFunction(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) // 如果鼠标按下，不区分左右键的
	{
		points[POINTSNUM].setxy(x, 480 - y); // 这里求鼠标点的坐标的时候
		// 设置点的颜色，绘制点
		glColor3f(1.0, 0.0, 0.0);
		setPoint(points[POINTSNUM]);
		// 设置线的颜色，绘制线
		glColor3f(1.0, 0.0, 0.0);
		if (POINTSNUM > 0) setline(points[POINTSNUM - 1], points[POINTSNUM]);

		//如果达到了4个绘制贝塞尔曲线，并在之后给计数器清零
		if (POINTSNUM == 3) {
			//绘制贝塞尔曲线   
			glColor3f(0.0, 0.0, 1.0); // 设定贝塞尔曲线的颜色

			Point p_current = points[0]; //设为起点
			for (double t = 0.0; t <= 1.0; t += 0.05)
			{
				Point P = setBezier(points[0], points[1], points[2], points[3], t);
				setline(p_current, P);
				p_current = P;
			}

			POINTSNUM = 0;
		}
		else {
			POINTSNUM++;
		}
	}
}

void Test3(int* argc, char *argv[])
{
	glutInit(argc, argv); //固定格式
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //缓存模式
	glutInitWindowSize(600, 480);    //显示框的大小
	glutInitWindowPosition(100, 100); //确定显示框左上角的位置
	glutCreateWindow("第四次作业");

	init(); // 初始化
	glutMouseFunc(mymouseFunction); // 添加鼠标事件
	glutDisplayFunc(display); // 执行显示   
	glutMainLoop(); //进人GLUT事件处理循环

}