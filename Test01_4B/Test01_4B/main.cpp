#include <stdio.h>
#include <stdlib.h>
#include "osapi/osapi.h"

//定义一个类
class Buddhist :public OS_Thread
{
public:
	int Start()
	{
		//启动准备工作
		m_quitflag = false;
		Run(); //启动线程
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
		//线程体：执行他的任务 
		//每次执行前检测线程是否退出
		for (int i = 0; !m_quitflag && i < 100; i++)
		{
			printf("和尚念经。。。\n");
			OS_Thread::Sleep(1); //静态函数
		}
		//保存数据，善后工作
		//...
		printf("保存已经完成数据，善后工作 Task Exit.... \n"); 
		return 0; //线程正常退出
	}
private:
	bool m_quitflag;
};


int main()
{

	Buddhist b;
	b.Start();

	getchar(); //输入回车 给出终止线程b的信号

   b.Stop(); //这里不属于自己调用自己  是在main中调用
   //Buddhist是一个类，C++中的一个类，对象，  只有Routine执行，才是线程执行
   
   
   getchar(); //输入回车 主线程退出

	return 0;
}