#pragma once
#include "GL\glut.h"
#include <math.h>
#include <Windows.h>

//����һ������࣬���ڴ洢���е������
class Point
{
public:
	int x, y;
	void setxy(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

//�������
static int POINTSNUM = 0;

//���ڴ洢��ļ���,��Ϊ���ƵĶ���4����ı��������ߣ����������СΪ4
static Point points[4];

//��ʼ������
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0); //�趨����Ϊ��ɫ
	glColor3f(0.0, 0.0, 0.0); //��ͼ��ɫΪ��ɫ
	glPointSize(2.0); //�趨��Ĵ�СΪ2*2���ص�
	glMatrixMode(GL_PROJECTION); // �趨���ʵľ���
	glLoadIdentity(); // ��һ���޲ε���ֵ�������书������һ��4��4�ĵ�λ�������滻��ǰ����ʵ���Ͼ��ǶԵ�ǰ������г�ʼ����Ҳ����˵��������ǰ�����˶��ٴξ���任���ڸ�����ִ�к󣬵�ǰ������ָ���һ����λ���󣬼��൱��û�н����κξ���任״̬
	gluOrtho2D(0.0, 600.0, 0.0, 480.0); //ƽ��ͶӰ���ĸ������ֱ���x,y��Χ
}

//���Ƶ�
void setPoint(Point p) {
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
	glFlush();
}

// ����ֱ��
void setline(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
	glFlush();
}

// ���Ʊ���������
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


//display����
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}



// ����¼�
void mymouseFunction(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) // �����갴�£����������Ҽ���
	{
		points[POINTSNUM].setxy(x, 480 - y); // ����������������ʱ��
		// ���õ����ɫ�����Ƶ�
		glColor3f(1.0, 0.0, 0.0);
		setPoint(points[POINTSNUM]);
		// �����ߵ���ɫ��������
		glColor3f(1.0, 0.0, 0.0);
		if (POINTSNUM > 0) setline(points[POINTSNUM - 1], points[POINTSNUM]);

		//����ﵽ��4�����Ʊ��������ߣ�����֮�������������
		if (POINTSNUM == 3) {
			//���Ʊ���������   
			glColor3f(0.0, 0.0, 1.0); // �趨���������ߵ���ɫ

			Point p_current = points[0]; //��Ϊ���
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
	glutInit(argc, argv); //�̶���ʽ
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);   //����ģʽ
	glutInitWindowSize(600, 480);    //��ʾ��Ĵ�С
	glutInitWindowPosition(100, 100); //ȷ����ʾ�����Ͻǵ�λ��
	glutCreateWindow("���Ĵ���ҵ");

	init(); // ��ʼ��
	glutMouseFunc(mymouseFunction); // �������¼�
	glutDisplayFunc(display); // ִ����ʾ   
	glutMainLoop(); //����GLUT�¼�����ѭ��

}