
#ifndef _AF_THREAD_H
#define _AF_THREAD_H

/* AfThread
   �߳��ࡣ�߳�����������Ϊ ThreadMain()

   ���ߣ��۷�
   �汾��2016-01-30
   ���°汾���ڹ��� http://afanihao.cn �ϻ�ȡ
*/

struct AfThread_Priv;
class AfThread
{
public:
	AfThread();
	virtual ~AfThread();

	// ����������
	virtual int Run();

	// �ȴ����ջ���Դ
	static void Join(AfThread* thrd);

	// Sleep����
	static void Msleep(int ms);
	static void Sleep(int s);

public:
	virtual int ThreadMain() = 0;

private:
	AfThread_Priv* m_Priv;
};


#endif

