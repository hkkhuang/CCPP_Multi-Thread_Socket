#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include "osapi/osapi.h"

int result;
OS_Mutex g_mutex;


// 求和: 1 + 2 + ... + n
int sum(int n)
{
	//加锁
	g_mutex.Lock();
	result = 0;
	for (int i = 1; i <= n; i++)
	{
		result += i;
	}
	int r = result;
	g_mutex.Unlock();  //释放锁

	return result;
}

//定义类
class MyTask : public OS_Thread
{
public:
	virtual int Routine()
	{
		while (1)
		{
			int ret = sum(100);
			if (ret != 5050)
			{
				printf("%d \n", ret);
			}
			
			OS_Thread::Msleep(5); //交出cpu 切换线程
		}
		return 0;
	}
};

int main()
{
	MyTask t;
	t.Run();

	MyTask t2;
	t2.Run();

	getchar();
	return 0;
}

