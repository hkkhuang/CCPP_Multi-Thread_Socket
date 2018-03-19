#include <stdio.h>
#include <stdlib.h>
#include "osapi/osapi.h"

int g_number = 100;  //����һȫ�ֱ��� gǰ׺��global��

//����һ����
class TaskA :public OS_Thread
{
private:
	virtual int Routine()
	{
		//�߳��壺ִ���������� 
		//ÿ��ִ��ǰ����߳��Ƿ��˳�
		for (int i = 0; !m_quitflag && i < 100; i++)
		{
			printf("TaskA: g_number: %d\n", g_number);
			OS_Thread::Sleep(1); //��̬����
		}
		return 0; //�߳������˳�
	}
private:
	bool m_quitflag;
};


class TaskB :public OS_Thread
{
private:
	virtual int Routine()
	{
		//�߳��壺ִ���������� 
		//ÿ��ִ��ǰ����߳��Ƿ��˳�
		for (int i = 0; !m_quitflag && i < 100; i++)
		{
			printf("TaskB: g_number: %d\n", g_number);
			OS_Thread::Sleep(1); //��̬����
		}
		return 0; //�߳������˳�
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
    getchar(); //����س� ���߳��˳�

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