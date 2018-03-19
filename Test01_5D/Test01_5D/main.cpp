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
			//��������������
			// ���ɸ���key ��Ҫ�϶�ʱ�� ���ڸ���ǰ������ɹ���
			//1. ����key
			char key_new[16];
			for (int i = 0; i < 16; i++)
			{
				OS_Thread::Msleep(5);
				key_new[i] = times; //ÿ�θ��¶��ǰ���������Ԫ�ظ�ֵΪ��ֵͬ
			}


			//���߳���Ҫ����g_data�������Ȼ�ȡ��
			//��ʼ����֮ǰ ����
			// 2.����key  ִ�и��µ�ʱ���ȡ��  ռ������ʱ��
			g_mutex.Lock(); // �˺���������,һֱ�ȴ�ӵ����
			//�ڸ��½׶ν��������ɵ�new keyֱ�Ӹ��Ƹ� ��Ҫ���µ�key
			memcpy(g_data, key_new, 16);
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
			//���账�����ݵ�ʱ�䳤 ���Ƚ����ݿ������� �ٽ��д���
			//�������̶Թ������ݵķ���ʱ��
			char key_copy[16];
			memcpy(key_copy, g_data, 16);
			g_mutex.Unlock(); // �ͷ���
			
			PrintKey();
			// ���������
			for (int i = 1; i < 16; i++)
			{
				OS_Thread::Msleep(5);
				if (key_copy[i] != key_copy[i - 1]) //����Ƚ�Ԫ��ֵ �Ƿ����
				{
					printf("������!!\n");
					PrintKey();
					return 0;
				}
			}
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