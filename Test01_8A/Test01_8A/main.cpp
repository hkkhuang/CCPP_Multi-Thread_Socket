#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */

#include <stdio.h>
#include <string.h>

#include <Windows.h>
#include <process.h> 

// ʹ��WindowsAPI �����߳�
unsigned int WINAPI OS_Thread_Proc(void* param)
{
	for (int i = 0; i < 10; i++)
	{
		printf("do my job: %d \n", i);
		Sleep(1000);
	}
	return 0;
}

int main()
{
	unsigned int thrdaddr;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0,
		OS_Thread_Proc, NULL,
		0, &thrdaddr);

	getchar();
	return 0;
}