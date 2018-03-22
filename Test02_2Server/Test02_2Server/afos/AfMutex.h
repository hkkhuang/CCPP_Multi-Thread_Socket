
#ifndef _OSAPI_MUTEX_H
#define _OSAPI_MUTEX_H

/* AfMutex
   互斥锁。

   作者：邵发
   版本：2016-01-30
   最新版本请在官网 http://afanihao.cn 上获取
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
	int Init(); // 创建

private:
	AfMutex_Priv* m_Priv;

};



#endif
