#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "osapi/osapi.h"

OS_Mutex g_mutex;
int g_buf[100]; //缓冲区 大小设置为100  存储100个数
int g_count = 0;

OS_Semaphore g_sem = 0; //设置信号量的初始值

//定义类 Producer
class Producer : public OS_Thread
{
public:
	virtual int Routine()
	{
		while (1)
		{
			//产生一个随机数 1-20之间
			int r = rand() % 20 + 1; 
			OS_Thread::Msleep(20 * r); //线程sleep时间为20-1000

			//存放物品 数字  
			g_mutex.Lock();//加锁
			g_buf[g_count] = r;
			g_count++;
			printf("Producer 放入物品：%d \n", r);
			g_mutex.Unlock(); //释放锁

			g_sem.Post(); //Producer放入物品 信号量 +1 即通知可取
		}
		return 0;
	}
};

//定义类 Consumer
class Consumer : public OS_Thread
{
public:
	virtual int Routine()
	{
		//轮询机制  频繁查询当前物品个数
		while (1)
		{
			//OS_Thread::Msleep(500);  //信号量机制不用sleep
			g_sem.Wait(); //Consumer 消费物品 信号量 -1

			g_mutex.Lock();
			if (g_count>0)
			{
				for (int i=0;i<g_count;i++)
				{
					printf("消费者拿走物品 %d \n", g_buf[i]);
				}
				g_count = 0;//消费者拿完物品 置为0
			}
			g_mutex.Unlock();//解锁
		}
		return 0;
	}
};


int main()
{
	srand(time(NULL));//随机数种子

	Producer p;
	p.Run();

	Producer p1;
	p1.Run();

	Consumer c;
	c.Run();

	getchar();
	return 0;
}

// Producer 放入物品：2
// 消费者拿走物品 2
// Producer 放入物品：8
// 消费者拿走物品 8
// Producer 放入物品：15
// 消费者拿走物品 15
// Producer 放入物品：1
// 消费者拿走物品 1
// Producer 放入物品：10
// 消费者拿走物品 10
// Producer 放入物品：5
// 消费者拿走物品 5
// Producer 放入物品：19
// 消费者拿走物品 19