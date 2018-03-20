
#ifndef _AF_THREAD_H
#define _AF_THREAD_H

/* AfThread
   线程类。线程主函数名称为 ThreadMain()

   作者：邵发
   版本：2016-01-30
   最新版本请在官网 http://afanihao.cn 上获取
*/

struct AfThread_Priv;
class AfThread
{
public:
	AfThread();
	virtual ~AfThread();

	// 创建并启动
	virtual int Run();

	// 等待和收回资源
	static void Join(AfThread* thrd);

	// Sleep函数
	static void Msleep(int ms);
	static void Sleep(int s);

public:
	virtual int ThreadMain() = 0;

private:
	AfThread_Priv* m_Priv;
};


#endif

