#include <stdio.h>
#include <stdlib.h>
#include "osapi/osapi.h"

//����һ����
class Buddhist :public OS_Thread
{
public:
	int Start()
	{
		//����׼������
		m_quitflag = false;
		Run(); //�����߳�
		return 0;
	}

	void Stop()
	{
		m_quitflag = true;
		Join(this);
	}
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
private:
	bool m_quitflag;
};


int main()
{

	Buddhist b;
	b.Start();

	getchar(); //����س� ������ֹ�߳�b���ź�

   b.Stop(); //���ﲻ�����Լ������Լ�  ����main�е���
   //Buddhist��һ���࣬C++�е�һ���࣬����  ֻ��Routineִ�У������߳�ִ��
   
   
   getchar(); //����س� ���߳��˳�

	return 0;
}