#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include "osapi/osapi.h"

//1. 创建全局对象，或堆对象
OS_Mutex g_mutex;
char g_data[128];


//更新共享数据
class KeyGenerator : public OS_Thread
{
private:
	virtual int Routine()
	{
		int times = 0;
		while (1)
		{
			//策略问题解决方法
			// 生成更新key 需要较多时间 则在更新前完成生成工作
			//1. 生成key
			char key_new[16];
			for (int i = 0; i < 16; i++)
			{
				OS_Thread::Msleep(5);
				key_new[i] = times; //每次更新都是把数组所有元素赋值为相同值
			}


			//在线程中要访问g_data，必须先获取锁
			//开始更新之前 加锁
			// 2.更新key  执行更新的时候获取锁  占有锁的时间
			g_mutex.Lock(); // 此函数会阻塞,一直等待拥有锁
			//在更新阶段将事先生成的new key直接复制给 需要更新的key
			memcpy(g_data, key_new, 16);
			//更新结束 释放锁
			g_mutex.Unlock(); // 释放锁

			times++;
			if (times >= 128) times = 0;
		}
		return 0;
	}
};

//读取数据 检查共享数据完整性
class KeyChecker : public OS_Thread
{
private:
	// 线程主函数
	virtual int Routine()
	{
		
		while (1)
		{
			//获得锁
			g_mutex.Lock(); // 此函数会阻塞,一直等待拥有锁
			//假设处理数据的时间长 则先将数据拷贝出来 再进行处理
			//尽量缩短对共享数据的访问时间
			char key_copy[16];
			memcpy(key_copy, g_data, 16);
			g_mutex.Unlock(); // 释放锁
			
			PrintKey();
			// 检查完整性
			for (int i = 1; i < 16; i++)
			{
				OS_Thread::Msleep(5);
				if (key_copy[i] != key_copy[i - 1]) //逐个比较元素值 是否都相等
				{
					printf("不完整!!\n");
					PrintKey();
					return 0;
				}
			}
		}
		return 0; // 正常退出
	}

	void PrintKey()
	{
		printf("Key: ");
		for (int i = 0; i < 16; i++)
			printf("%02X ", g_data[i]);
		printf("\n");
	}
};


int main()
{
	KeyGenerator a;
	a.Run();

	KeyChecker b;
	b.Run();

	getchar();
	return 0;
}

//使用互斥锁  保证数据的完整性