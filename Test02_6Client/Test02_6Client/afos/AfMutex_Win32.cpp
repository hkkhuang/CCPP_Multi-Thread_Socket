
#include "AfMutex.h"

#ifdef _WIN32
#include <windows.h>

struct AfMutex_Priv
{
	HANDLE hMutex;
};

AfMutex::AfMutex()
:m_Priv(NULL)
{
	Init();
}

AfMutex::~AfMutex()
{
	if(m_Priv) 
	{
		CloseHandle(m_Priv->hMutex);
		delete m_Priv;
	}
}

int AfMutex::Init()
{
	m_Priv = new AfMutex_Priv;
	m_Priv->hMutex = CreateMutex(NULL, true, NULL);
	if(m_Priv->hMutex == NULL)
	{
		delete m_Priv;
		m_Priv = NULL;
		return -1;
	}

	ReleaseMutex(m_Priv->hMutex);
	return 0;
}

int AfMutex::Lock()
{
	if(!m_Priv) return -1;

	WaitForSingleObject(m_Priv->hMutex, INFINITE);
	return 0;
}

int AfMutex::TryLock()
{
	if(!m_Priv) return -1;

	DWORD  ret = WaitForSingleObject(m_Priv->hMutex, 1);	
	if( ret == WAIT_OBJECT_0)
	{
		return 0; // success
	}
	if( ret == WAIT_TIMEOUT)
	{
		return -1; // timeout
	}
	return -1;
}

void AfMutex::Unlock()
{
	if(!m_Priv) return;
	ReleaseMutex(m_Priv->hMutex);
}

#endif





