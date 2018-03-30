
#ifndef _TCP_CONN_H
#define _TCP_CONN_H

#include "afos/AfSocket.h"
#include "afos/AfThread.h"

/* TcpConn:
   用一个线程来维护Client - WorkingSocket之间的通话连接
*/

class TcpConn : public AfThread
{
public:
	TcpConn(AfTcpSocket work_sock);
	~TcpConn();

private:
	virtual int ThreadMain(); //必须重写

private:
	AfTcpSocket m_WorkSock;
};




#endif

