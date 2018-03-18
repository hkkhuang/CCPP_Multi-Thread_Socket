#include <stdio.h>
#include <stdlib.h>
#include "osapi/osapi.h"

//定义一个类
class Buddhist :public OS_Thread
{
	virtual int Routine()
	{
		for (int i = 0; i < 100; i++)
		{
			printf("和尚念经。。。。\n");
			//线程 睡眠暂停
			//OS_Thread::Sleep(1);  //秒为量级
			OS_Thread::Msleep(100); //毫秒为量级
		}
		return 0;
	}
};
int main()
{
	Buddhist b;
	b.Run();

	getchar();
	return 0;
}