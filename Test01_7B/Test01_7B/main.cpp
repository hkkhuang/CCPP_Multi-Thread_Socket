#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "osapi/osapi.h"

OS_Mutex g_mutex;
int g_buf[100]; //������ ��С����Ϊ100  �洢100����
int g_count = 0;

OS_Semaphore g_sem = 0; //�����ź����ĳ�ʼֵ

//������ Producer
class Producer : public OS_Thread
{
public:
	virtual int Routine()
	{
		while (1)
		{
			//����һ������� 1-20֮��
			int r = rand() % 20 + 1; 
			OS_Thread::Msleep(20 * r); //�߳�sleepʱ��Ϊ20-1000

			//�����Ʒ ����  
			g_mutex.Lock();//����
			g_buf[g_count] = r;
			g_count++;
			printf("Producer ������Ʒ��%d \n", r);
			g_mutex.Unlock(); //�ͷ���

			g_sem.Post(); //Producer������Ʒ �ź��� +1 ��֪ͨ��ȡ
		}
		return 0;
	}
};

//������ Consumer
class Consumer : public OS_Thread
{
public:
	virtual int Routine()
	{
		//��ѯ����  Ƶ����ѯ��ǰ��Ʒ����
		while (1)
		{
			//OS_Thread::Msleep(500);  //�ź������Ʋ���sleep
			g_sem.Wait(); //Consumer ������Ʒ �ź��� -1

			g_mutex.Lock();
			if (g_count>0)
			{
				for (int i=0;i<g_count;i++)
				{
					printf("������������Ʒ %d \n", g_buf[i]);
				}
				g_count = 0;//������������Ʒ ��Ϊ0
			}
			g_mutex.Unlock();//����
		}
		return 0;
	}
};


int main()
{
	srand(time(NULL));//���������

	Producer p;
	p.Run();

	Producer p1;
	p1.Run();

	Consumer c;
	c.Run();

	getchar();
	return 0;
}

// Producer ������Ʒ��2
// ������������Ʒ 2
// Producer ������Ʒ��8
// ������������Ʒ 8
// Producer ������Ʒ��15
// ������������Ʒ 15
// Producer ������Ʒ��1
// ������������Ʒ 1
// Producer ������Ʒ��10
// ������������Ʒ 10
// Producer ������Ʒ��5
// ������������Ʒ 5
// Producer ������Ʒ��19
// ������������Ʒ 19