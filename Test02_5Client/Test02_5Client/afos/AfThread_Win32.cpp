
#ifdef _WIN32

#include <windows.h>
#include <process.h> 

#include "AfThread.h"

struct AfThread_Priv
{
	HANDLE hThread;
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

static DWORD WINAPI OS_Thread_Proc_Win32_1(LPVOID param)
{
	AfThread* thrd = (AfThread*) param;
	thrd->ThreadMain();

	return 0;
}

static void OS_Thread_Proc_Win32_2(void* param)
{
	AfThread* thrd = (AfThread*) param;
	thrd->ThreadMain();
}

static unsigned int WINAPI OS_Thread_Proc_Win32_3(void* param)
{
	AfThread* thrd = (AfThread*) param;
	thrd->ThreadMain();
	return 0;
}

int AfThread::Run()
{
	// 创建私有结构
	m_Priv = new AfThread_Priv;

	// 创建线程
// 	DWORD nTheadId;
// 	priv->hThread = _beginthreadex(NULL, NULL, OS_Thread_Proc_Win32, this,  0, &nTheadId);
// 	priv->hThread = (HANDLE) _beginthread(OS_Thread_Proc_Win32, 0, this);
	unsigned int thrdaddr ;
	m_Priv->hThread = (HANDLE) _beginthreadex(NULL, 0, OS_Thread_Proc_Win32_3, this, 0, &thrdaddr);
	if(m_Priv->hThread == NULL)
	{
		delete m_Priv;
		m_Priv = NULL;
		return -1;
	}

	return 0;
}

void AfThread::Join(AfThread* thrd)
{
	AfThread_Priv* priv = thrd->m_Priv;
	if(priv)
	{
		WaitForSingleObject(priv->hThread, INFINITE);
 		CloseHandle(priv->hThread);
		// 删除资源
		delete priv;
		thrd->m_Priv = NULL;
	}
}

void AfThread::Msleep(int ms)
{
	::Sleep(ms);
}

void AfThread::Sleep(int s)
{
	::Sleep(s * 1000);
}

int AfThread::ThreadMain()
{
	return 0;
}

#endif  //_WIN32


