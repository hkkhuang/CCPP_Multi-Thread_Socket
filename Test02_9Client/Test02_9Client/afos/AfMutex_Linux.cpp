
#include "AfMutex.h"

#ifndef _WIN32
//#if 1

#include <pthread.h>

struct AfMutex_Priv
{
	pthread_mutex_t hMutex;
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
		AfMutex_Priv* priv = (AfMutex_Priv*) m_Priv;
		pthread_mutex_destroy(&priv->hMutex);
		delete priv;
	}
}

int AfMutex::Init()
{
	AfMutex_Priv* priv = new AfMutex_Priv;
	if(!priv) return -1;
	m_Priv = priv;

	// ´´½¨mutex
	if(pthread_mutex_init(&priv->hMutex, NULL) < 0)
	{
		delete priv;
		m_Priv = NULL;
		return -1;
	}

	return 0;
}

int AfMutex::Lock()
{
	AfMutex_Priv* priv = (AfMutex_Priv*) m_Priv;
	if(!priv) return -1;

	if( pthread_mutex_lock(&priv->hMutex) < 0)
	{
		return -1;
	}

	return 0;
}

int AfMutex::TryLock()
{
	AfMutex_Priv* priv = (AfMutex_Priv*) m_Priv;
	if(!priv) return -1;

	if(pthread_mutex_trylock(&priv->hMutex) < 0)
	{
		return -1;
	}

	return 0;
}

void AfMutex::Unlock()
{
	AfMutex_Priv* priv = (AfMutex_Priv*) m_Priv;
	if(!priv ) return;

	pthread_mutex_unlock(&priv->hMutex);
}



#endif  // ! _WIN32


