#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include "osapi/osapi.h"

int result;
OS_Mutex g_mutex;


// ���: 1 + 2 + ... + n
int sum(int n)
{
	//����
	g_mutex.Lock();
	result = 0;
	for (int i = 1; i <= n; i++)
	{
		result += i;
	}
	int r = result;
	g_mutex.Unlock();  //�ͷ���

	return result;
}

//������
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
			
			OS_Thread::Msleep(5); //����cpu �л��߳�
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

