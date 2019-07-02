/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*

*********************************************************************************************************
*/
/*
for book:嵌入式实时操作系统μCOS原理与实践
卢有亮
2011于成都电子科技大学
*/
#include "includes.h"

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE               512       /* Size of each task's stacks (# of WORDs)            */
#define TaskStart_Prio	1
#define Task1_Prio		2





OS_STK  TaskStk[OS_MAX_TASKS][TASK_STK_SIZE];    // Tasks stacks
HANDLE mainhandle;		//主线程句柄
CONTEXT Context;		//主线程切换上下文
BOOLEAN FlagEn = 1;		//增加一个全局变量，做为是否时钟调度的标志


void TaskStart(void * pParam) ;
//void Task1(void * pParam) ;                            /* Function prototypes of tasks                  */

void VCInit(void);						//初始化相关变量,一定需要

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/


int main(int argc, char **argv)
{
	int p[2],Experiment ;
	p[0]=0;
	p[1]=100;
	VCInit();
    printf("0.没有用户任务\n");
    printf("1.第一个例子，一个用户任务\n");
    printf("2.第二个例子，两个任务共享CPU交替运行\n");
    printf("3.第三个例子，任务的挂起和恢复\n");
    printf("4.第四个例子，信号量管理\n");
    printf("5.第五个例子，互斥信号量管理\n"); 
    printf("6.第六个例子，事件标志组\n");
    printf("7.第七个例子，消息邮箱\n");
    printf("8.第八个例子，消息队列\n");
    printf("9.第九个例子，内存管理\n"); 
	
    printf("请输入序号选择例子:\n");
	scanf("%d",&Experiment);
    if ((Experiment<0)||(Experiment>10))
	{
		printf("无效的输入!");
        return(1); 	
	}
	OSInit();
	OSTaskCreate(TaskStart, 0, &TaskStk[1][TASK_STK_SIZE-1], TaskStart_Prio);
	switch(Experiment) 
	{
		case 1://一个任务运行
			OSTaskCreate(FirstTask, 0, &TaskStk[5][TASK_STK_SIZE-1], 5);
			break;
		case 2://两个任务共享CPU
			OSTaskCreate(E2_task1, 0, &TaskStk[5][TASK_STK_SIZE-1], 5);
			OSTaskCreate(E2_task2, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
            break;
		case 3://任务的挂起和恢复
			OSTaskCreate(E3_task0, 0, &TaskStk[5][TASK_STK_SIZE-1], 5);
			OSTaskCreate(E3_task1, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
			OSTaskCreate(E3_task2, 0, &TaskStk[7][TASK_STK_SIZE-1], 7);
            break;
		case 4://信号量管理例程
			OSTaskCreate(UserTaskSemA, 0, &TaskStk[5][TASK_STK_SIZE-1], 7);
			OSTaskCreate(UserTaskSemB, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
			OSTaskCreate(UserTaskSemC, 0, &TaskStk[7][TASK_STK_SIZE-1], 5);
            break;
		case 5://互斥信号量管理例程
			OSTaskCreate(TaskMutex1, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
			OSTaskCreate(TaskMutex2, 0, &TaskStk[7][TASK_STK_SIZE-1], 50);
			OSTaskCreate(TaskPrint, 0, &TaskStk[8][TASK_STK_SIZE-1], 30);
            break;
		case 6://时间标志组管理例程
			OSTaskCreate(TaskDataProcess, 0, &TaskStk[5][TASK_STK_SIZE-1],5);
			OSTaskCreate(TaskIO1, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
			OSTaskCreate(TaskIO2, 0, &TaskStk[7][TASK_STK_SIZE-1], 7);
			OSTaskCreate(TaskIO3, 0, &TaskStk[8][TASK_STK_SIZE-1], 8);
			OSTaskCreate(TaskIO4, 0, &TaskStk[9][TASK_STK_SIZE-1], 9);
            break;
		case 7://消息邮箱
			OSTaskCreate(TaskMessageSen, 0, &TaskStk[6][TASK_STK_SIZE-1], 6);
			OSTaskCreate(TaskMessageRec, 0, &TaskStk[7][TASK_STK_SIZE-1], 7);
			break;
		case 8://消息队列
			 OSTaskCreate(TaskQSen, 0, &TaskStk[7][TASK_STK_SIZE-1], 5);
			 OSTaskCreate(TaskQRec, 0, &TaskStk[8][TASK_STK_SIZE-1], 6);
			 OSTaskCreate(TaskQRec, 0, &TaskStk[9][TASK_STK_SIZE-1], 7);
			break;
		case 9://内存管理
			 OSTaskCreate(TaskM, 0, &TaskStk[8][TASK_STK_SIZE-1], 6);
			break;
		default:           
			;
	}
 
	OSStart();	       
	return(0);
}

void VCInit(void)
{
	HANDLE cp,ct;
	Context.ContextFlags = CONTEXT_CONTROL;
	cp = GetCurrentProcess();	//得到当前进程句柄
	ct = GetCurrentThread();	//得到当前线程伪句柄
	DuplicateHandle(cp, ct, cp, &mainhandle, 0, TRUE, 2);	//伪句柄转换,得到线程真句柄
		
}

void TaskStart(void * pParam) 
{	
	char err;	
	OS_EVENT *sem1;
    
	/*模拟设置定时器中断。开启一个定时器线程,每秒中断100次,中断服务程序OSTickISRuser*/
	timeSetEvent(1000/OS_TICKS_PER_SEC, 0, OSTickISRuser, 0, TIME_PERIODIC);
	OSStatInit(); /*统计任务初始化*/
	sem1 = OSSemCreate(0); 
	OSSemPend(sem1, 0, &err);   //等待事件发生，被阻塞；
}
