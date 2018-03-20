
#include "AfSem.h"

#ifndef _WIN32
//#if 1
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 

struct AfSem_Priv
{
	sem_t hSem;
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
		sem_destroy(&priv->hSem);
		delete priv;
	}
}

int AfSem::Init(int initial_value)
{
	AfSem_Priv* priv = new AfSem_Priv;
	if(!priv) return -1;
	m_Priv = priv;

	if(sem_init(&priv->hSem, 1, initial_value) < 0)
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

	if(sem_wait(&priv->hSem) < 0)
	{
		return -1;
	}

	return 0;
}

int AfSem::Wait(int ms)
{
	AfSem_Priv* priv = (AfSem_Priv*) m_Priv;
	if(!priv) return -1;

	timeval tv_now;
	gettimeofday(&tv_now, NULL);

	timespec ts;
	ts.tv_sec = tv_now.tv_sec;
	ts.tv_nsec = tv_now.tv_usec * 1000;

	int ns = ts.tv_nsec + (ms % 1000)  * 1000000;
	ts.tv_nsec = ns % 1000000000;
	ts.tv_sec += ns / 1000000000;
	ts.tv_sec += ms / 1000;

	if(sem_timedwait(&priv->hSem, &ts) != 0)
	{
		return -1;
	}

	return 0;;
}

void AfSem::Post()
{
	AfSem_Priv* priv = (AfSem_Priv*) m_Priv;
	if(!priv) return;

	sem_post(&priv->hSem);
}

#endif // ! _WIN32


