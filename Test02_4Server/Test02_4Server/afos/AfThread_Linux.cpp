
#ifndef _WIN32
//#if 1
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "AfThread.h"


struct AfThread_Priv
{
	pthread_t hThread;
};

AfThread::AfThread() 
: m_Priv(NULL)
{
}

AfThread::~AfThread()
{
	if(m_Priv)
	{
		delete m_Priv;
	}
}

static void* OS_Thread_Proc_Linux(void* param)
{
	AfThread* thrd = (AfThread*) param;
	thrd->ThreadMain();
	return NULL;
}

int AfThread::Run()
{
	// 创建私有结构
	m_Priv = new AfThread_Priv;

	// 创建线程
	if(pthread_create(&m_Priv->hThread, NULL, OS_Thread_Proc_Linux, this) < 0)
	{
		delete m_Priv;
		m_Priv = NULL;
		return -1;
	}

	return 0;
}

void AfThread::Join(AfThread* thrd)
{
	if(m_Priv)
	{
		pthread_join(m_Priv->hThread, NULL);

		// 删除资源
		delete m_Priv;
		thrd->m_Priv = NULL;
	}
}

void AfThread::Msleep(int ms)
{
	//::usleep(ms * 1000);
	// 好像使用nanosleep更好

	timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	nanosleep(&ts, NULL);
}

void AfThread::Sleep(int s)
{
	::sleep(s);
}

int AfThread::ThreadMain()
{
	return 0;
}



#endif // ! _WIN32


