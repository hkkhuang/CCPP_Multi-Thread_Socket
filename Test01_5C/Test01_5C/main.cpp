#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include "osapi/osapi.h"

//1. ����ȫ�ֶ��󣬻�Ѷ���
OS_Mutex g_mutex;
char g_data[128];


//���¹�������
class KeyGenerator : public OS_Thread
{
private:
	virtual int Routine()
	{
		int times = 0;
		while (1)
		{
			//2. ���߳���Ҫ����g_data�������Ȼ�ȡ��
			//��ʼ����֮ǰ ����
			g_mutex.Lock(); // �˺���������,һֱ�ȴ�ӵ����
			// ����key
			for (int i = 0; i < 16; i++)
			{
				g_data[i] = times; //ÿ�θ��¶��ǰ���������Ԫ�ظ�ֵΪ��ֵͬ
			}
			//���½��� �ͷ���
			g_mutex.Unlock(); // �ͷ���

			times++;
			if (times >= 128) times = 0;
		}
		return 0;
	}
};

//��ȡ���� ��鹲������������
class KeyChecker : public OS_Thread
{
private:
	// �߳�������
	virtual int Routine()
	{
		
		while (1)
		{
			//�����
			g_mutex.Lock(); // �˺���������,һֱ�ȴ�ӵ����
			PrintKey();
			// ���������
			for (int i = 1; i < 16; i++)
			{
				if (g_data[i] != g_data[i - 1]) //����Ƚ�Ԫ��ֵ �Ƿ����
				{
					printf("������!!\n");
					PrintKey();
					return 0;
				}
			}
			g_mutex.Unlock(); // �ͷ���
		}
		
		return 0; // �����˳�
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

//ʹ�û�����  ��֤���ݵ�������