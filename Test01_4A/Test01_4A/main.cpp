#include <stdio.h>
#include <stdlib.h>
#include "osapi/osapi.h"

//����һ����
class Buddhist :public OS_Thread
{
private:
	virtual int Routine()
	{
		//�߳��壺ִ���������� 
		//ÿ��ִ��ǰ����߳��Ƿ��˳�
		for (int i = 0; !m_quitflag && i < 100; i++)
		{
			printf("�����������\n");
			OS_Thread::Sleep(1); //��̬����
		}
		//�������ݣ��ƺ���
		//...
		printf("�����Ѿ�������ݣ��ƺ��� Task Exit.... \n"); 
		return 0; //�߳������˳�
	}
public:
	bool m_quitflag;
};

//����һ����
class Confucian :public OS_Thread
{
private:
	virtual int Routine()
	{
		//�߳��壺ִ����������
		//ÿ��ִ��ǰ����߳��Ƿ��˳�
		for (int i = 0; i < 500; i++)
		{
			printf("��Ŷ��顣����\n");
			OS_Thread::Sleep(1); //��̬����
		}

		return 0;
	}
};


int main()
{

	Buddhist b;
	b.m_quitflag = false; //���˳�
	b.Run();  //�߳�1
	b.m_quitflag = true; //�˳�
	OS_Thread::Join(&b); // ʹ�þ�̬����Join()�����ȴ�Ŀ���߳��˳���


	Confucian c;
	c.Run(); //�߳�2

	

	getchar(); //����س� ���߳��˳�
	return 0;
}