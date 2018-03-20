
#include "AfSem.h"

#ifdef _WIN32
#include <windows.h>

struct AfSem_Priv
{
	HANDLE hSem;
};

AfSem::AfSem(int initial_value)
:m_Priv (NULL)
{
	Init(initial_value);
}

AfSem::~AfSem()
{
	if(m_Priv)
	{
		AfSem_Priv* priv = (AfSem_Priv*) m_Priv;
		delete priv;
	}
}

int AfSem::Init(int initial_value)
{
	AfSem_Priv* priv = new AfSem_Priv;
	if(!priv) return -1;
	m_Priv = priv;

	priv->hSem = CreateSemaphore(NULL, initial_value, 5000, NULL);
	if(priv->hSem == NULL)
	{
		delete priv;
		m_Priv = NULL;
		return -1;
	}

	return 0;
}

int AfSem::Wait()
{
	AfSem_Priv* priv = (AfSem_Priv*) m_Priv;
	if(!priv) return -1;

	WaitForSingleObject(priv->hSem, INFINITE);
	return 0;
}

int AfSem::Wait(int ms)
{
	AfSem_Priv* priv = (AfSem_Priv*) m_Priv;
	if(!priv) return -1;

	DWORD  ret = WaitForSingleObject(priv->hSem, ms);	
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

void AfSem::Post()
{
	AfSem_Priv* priv = (AfSem_Priv*) m_Priv;
	if(!priv) return;

	ReleaseSemaphore(priv->hSem, 1, NULL);
}


#endif // _WIN32


