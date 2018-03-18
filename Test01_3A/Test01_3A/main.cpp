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
		for (int i = 0; i < 100; i++)
		{
			printf("和尚念经。。。\n");
			OS_Thread::Sleep(1); //静态函数
		}

		return 0;
	}
};

//定义一个类
class Confucian :public OS_Thread
{
private:
	virtual int Routine()
	{
		//线程体：执行他的任务
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
	//设置断点，观察 资源监视器 线程数量   1
	Buddhist b;
	b.Run();
	//设置断点，观察 资源监视器 线程数量 2

	Confucian c;
	c.Run();
	//设置断点，观察 资源监视器 线程数量 3

	//两个子线程同时工作，主线程也可以工作，不影响
	printf("-------------main主线程开始工作-------------\n");
	for (int i = 0; i < 100; i++)
	{
		printf("管理人员开始工作。。。。。。。。。\n");
		//主线程在执行的过程中也是需要sleep,让出cpu
		OS_Thread::Sleep(1);
	}
	getchar();
	return 0;
}
