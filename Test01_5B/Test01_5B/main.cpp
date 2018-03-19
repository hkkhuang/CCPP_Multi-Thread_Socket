#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include "osapi/osapi.h"

char g_key[16]; // Generator��������Checker��ȡ��  ��������

//���¹�������
class KeyGenerator : public OS_Thread
{
private:
	virtual int Routine()
	{
		int times = 0;
		while (1)
		{

			// ����key
			for (int i = 0; i < 16; i++)
			{
				g_key[i] = times; //ÿ�θ��¶��ǰ���������Ԫ�ظ�ֵΪ��ֵͬ
				OS_Thread::Msleep(5); //��Ϊ���ã���֤��������  ����һ����Ҫ80ms
			}

			times++;
			if (times >= 128) times = 0;
			OS_Thread::Msleep(50); //ÿ50ms����һ��key
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
			PrintKey();
			// ���������
			for (int i = 1; i < 16; i++)
			{
				OS_Thread::Msleep(5); //��Ϊ���ã���֤��������  ��ȡһ����Ҫ80ms
				if (g_key[i] != g_key[i - 1]) //����Ƚ�Ԫ��ֵ �Ƿ����
				{
					printf("������!!\n");
					PrintKey();
					return 0;
				}
			}

			OS_Thread::Msleep(50);
		}
		return 0; // �����˳�
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
//Key : 02 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01  �����̻߳�û�и������ ��ȡ����߳̾Ϳ�ʼ��ȡ��֤������
//������!!