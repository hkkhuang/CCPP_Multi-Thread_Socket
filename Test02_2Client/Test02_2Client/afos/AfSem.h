
#ifndef  _AF_SEM_H
#define _AF_SEM_H

/* AfMutex
   信号量。

   作者：邵发
   版本：2016-01-30
   最新版本请在官网 http://afanihao.cn 上获取
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
	int Init(int initial_value=1); // 创建

private:
	void* m_Priv;
};


#endif

