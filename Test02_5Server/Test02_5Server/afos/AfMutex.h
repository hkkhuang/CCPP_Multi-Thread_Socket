
#ifndef _OSAPI_MUTEX_H
#define _OSAPI_MUTEX_H

/* AfMutex
   ��������

   ���ߣ��۷�
   �汾��2016-01-30
   ���°汾���ڹ��� http://afanihao.cn �ϻ�ȡ
*/

struct AfMutex_Priv;
class AfMutex
{
public:
	AfMutex();
	~AfMutex();


	int Lock();
	int TryLock();
	void Unlock();

private:
	int Init(); // ����

private:
	AfMutex_Priv* m_Priv;

};



#endif
