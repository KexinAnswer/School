#pragma once

#if 0
#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
//<<<<<<<<<<<<<<<<<<< axis >>>>>>>>>>>>>>
void axis(double length)
{ // draw a z-axis, with cone at end
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0); glVertex3d(0, 0, length); // along the z-axis
	glEnd();
	glTranslated(0, 0, length - 0.2);
	glutWireCone(0.04, 0.2, 12, 9);
	glPopMatrix();
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displayWire(void)
{
	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 100);//正射投影函数
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//define viewpoint transformation

	//Draw axis
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	glColor3d(0, 0, 0); // draw black lines
	axis(0.5);					 // z-axis
	glPushMatrix();
	glRotated(90, 0, 1.0, 0);
	axis(0.5);					// y-axis
	glRotated(-90.0, 1, 0, 0);
	axis(0.5);					// z-axis
	glPopMatrix();

	//Draw Cube
	glPushMatrix();
	glTranslated(0.5, 0.5, 0.5); // multiply by a translation matrix, define center (0.5, 0.5, 0.5)
	glutWireCube(1.0);
	glPopMatrix();

	//Draw Sphere
	glPushMatrix();
	glTranslated(1.0, 1.0, 0);	// sphere at (1,1,0)
	glutWireSphere(0.25, 10, 8);
	glPopMatrix();

	//Draw Cone
	glPushMatrix();
	glTranslated(1.0, 0, 1.0);	// cone at (1,0,1)
	glutWireCone(0.2, 0.5, 10, 8);
	glPopMatrix();

	//Draw Teapot
	glPushMatrix();
	glTranslated(1, 1, 1);
	glutWireTeapot(0.2); // teapot at (1,1,1)
	glPopMatrix();

	//Draw Torus
	glPushMatrix();
	glTranslated(0, 1.0, 0); // torus at (0,1,0)
	glRotated(90.0, 1, 0, 0);
	glutWireTorus(0.1, 0.3, 10, 10);
	glPopMatrix();

	//十二面体
	glPushMatrix();
	glTranslated(1.0, 0, 0); // dodecahedron at (1,0,0)
	glScaled(0.15, 0.15, 0.15);
	glutWireDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.0, 1.0); // small cube at (0,1,1)
	glutWireCube(0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, 1.0); // cylinder at (0,0,1)
	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.2, 0.2, 0.4, 8, 8);
	glPopMatrix();
	glFlush();
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Test4(int* argc, char **argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Transformation testbed - wireframes");
	glutDisplayFunc(displayWire);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white
	glViewport(0, 0, 640, 480);//投影变换函数
	glutMainLoop();
}
#endif


#if 1
#include <GL/glut.h>

GLint winWidth = 600, winHeight = 600; //设置初始化窗口大小

/* 观察坐标系参数设置*/

GLfloat x0 = 0.0, y0 = 0.0, z0 = 5.0; // 设置观察坐标系原点

GLfloat xref = 0.0, yref = 0.0, zref = 0.0; //设置观察坐标系参考点（视点）

GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // 设置观察坐标系向上向量（y轴）

/*观察体（视见体）参数设置 */

GLfloat xwMin = -1.0, ywMin = -1.0, xwMax = 1.0, ywMax = 1.0;//设置裁剪窗口坐标范围

GLfloat dnear = 1.5, dfar = 20.0;//设置远、近裁剪面深度范围

void init(void)

{

	glClearColor(1.0, 1.0, 1.0, 0.0);

	//glShadeModel (GL_FLAT);//xz

	/*①观察变换*/

	/*视点变换*/

	gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz); //指定三维观察参数

	/*模型变换*/

	glMatrixMode(GL_MODELVIEW);

	glScalef(2.0, 2.0, 2.0); //比例放缩变换

	glRotatef(45.0, 0.0, 1.0, 1.0);//旋转变换

	/*②投影变换*/

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);//透视投影，设置透视视景体

}

void displayFcn(void)

{

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 0.0); // 设置前景色为绿色

	glutSolidCube(1.0);//绘制单位立方体实体

	glColor3f(0.0, 0.0, 0.0); // 设置前景色为黑色

	glLineWidth(2.0); //设置线宽

	glutWireCube(1.0);//绘制单位立方体线框

	glFlush();

}

void reshapeFcn(GLint newWidth, GLint newHeight)

{

	/*③视口变换 */

	glViewport(0, 0, newWidth, newHeight);//定义视口大小

	winWidth = newWidth;

	winHeight = newHeight;

}

void Test4(int* argc, char** argv)

{

	glutInit(argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(100, 100);

	glutInitWindowSize(winWidth, winHeight);

	glutCreateWindow("单位立方体的透视投影");

	init();

	glutDisplayFunc(displayFcn);

	glutReshapeFunc(reshapeFcn);

	glutMainLoop();

}

#endif