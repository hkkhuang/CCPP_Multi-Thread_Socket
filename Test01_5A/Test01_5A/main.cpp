#include <stdio.h>
#include <stdlib.h>
#include "osapi/osapi.h"

int g_number = 100;  //定义一全局变量 g前缀（global）

//定义一个类
class TaskA :public OS_Thread
{
private:
	virtual int Routine()
	{
		//线程体：执行他的任务 
		//每次执行前检测线程是否退出
		for (int i = 0; !m_quitflag && i < 100; i++)
		{
			printf("TaskA: g_number: %d\n", g_number);
			OS_Thread::Sleep(1); //静态函数
		}
		return 0; //线程正常退出
	}
private:
	bool m_quitflag;
};


class TaskB :public OS_Thread
{
private:
	virtual int Routine()
	{
		//线程体：执行他的任务 
		//每次执行前检测线程是否退出
		for (int i = 0; !m_quitflag && i < 100; i++)
		{
			printf("TaskB: g_number: %d\n", g_number);
			OS_Thread::Sleep(1); //静态函数
		}
		return 0; //线程正常退出
	}
private:
	bool m_quitflag;
};

int main()
{

	TaskA task1;
	task1.Run();

	TaskB task2;
	task2.Run();
    getchar(); //输入回车 主线程退出

	return 0;
}
//
//TaskB: g_number: 100
//TaskA : g_number : 100
//TaskB : g_number : 100
//TaskA : g_number : 100
//TaskB : g_number : 100
//TaskA : g_number : 100
//TaskB : g_number : 100