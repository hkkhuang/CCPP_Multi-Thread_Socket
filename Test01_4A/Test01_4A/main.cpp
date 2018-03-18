#include <stdio.h>
#include <stdlib.h>
#include "osapi/osapi.h"

//定义一个类
class Buddhist :public OS_Thread
{
private:
	virtual int Routine()
	{
		//线程体：执行他的任务 
		//每次执行前检测线程是否退出
		for (int i = 0; !m_quitflag && i < 100; i++)
		{
			printf("和尚念经。。。\n");
			OS_Thread::Sleep(1); //静态函数
		}
		//保存数据，善后工作
		//...
		printf("保存已经完成数据，善后工作 Task Exit.... \n"); 
		return 0; //线程正常退出
	}
public:
	bool m_quitflag;
};

//定义一个类
class Confucian :public OS_Thread
{
private:
	virtual int Routine()
	{
		//线程体：执行他的任务
		//每次执行前检测线程是否退出
		for (int i = 0; i < 500; i++)
		{
			printf("秀才读书。。。\n");
			OS_Thread::Sleep(1); //静态函数
		}

		return 0;
	}
};


int main()
{

	Buddhist b;
	b.m_quitflag = false; //不退出
	b.Run();  //线程1
	b.m_quitflag = true; //退出
	OS_Thread::Join(&b); // 使用静态函数Join()，来等待目标线程退出。


	Confucian c;
	c.Run(); //线程2

	

	getchar(); //输入回车 主线程退出
	return 0;
}