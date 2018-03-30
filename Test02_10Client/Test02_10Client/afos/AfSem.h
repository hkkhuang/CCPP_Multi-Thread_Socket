
#ifndef  _AF_SEM_H
#define _AF_SEM_H

/* AfMutex
   �ź�����

   ���ߣ��۷�
   �汾��2016-01-30
   ���°汾���ڹ��� http://afanihao.cn �ϻ�ȡ
*/

class AfSem
{
public:
	AfSem(int initial_value=1);
	~AfSem();


	int Wait();
	int Wait(int ms);
	void Post();

private:
	int Init(int initial_value=1); // ����

private:
	void* m_Priv;
};


#endif

