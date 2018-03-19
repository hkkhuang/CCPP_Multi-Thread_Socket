#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include "osapi/osapi.h"

char g_key[16]; // Generator更新它，Checker获取它  共享数据

//更新共享数据
class KeyGenerator : public OS_Thread
{
private:
	virtual int Routine()
	{
		int times = 0;
		while (1)
		{

			// 更新key
			for (int i = 0; i < 16; i++)
			{
				g_key[i] = times; //每次更新都是把数组所有元素赋值为相同值
				OS_Thread::Msleep(5); //认为设置，验证不完整行  更新一次需要80ms
			}

			times++;
			if (times >= 128) times = 0;
			OS_Thread::Msleep(50); //每50ms更新一次key
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
			PrintKey();
			// 检查完整性
			for (int i = 1; i < 16; i++)
			{
				OS_Thread::Msleep(5); //认为设置，验证不完整行  读取一次需要80ms
				if (g_key[i] != g_key[i - 1]) //逐个比较元素值 是否都相等
				{
					printf("不完整!!\n");
					PrintKey();
					return 0;
				}
			}

			OS_Thread::Msleep(50);
		}
		return 0; // 正常退出
	}

	void PrintKey()
	{
		printf("Key: ");
		for (int i = 0; i < 16; i++)
			printf("%02X ", g_key[i]);
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


//Key: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
//Key : 01 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00
//Key : 02 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01  更新线程还没有更新完毕 读取检查线程就开始读取验证完整性
//不完整!!