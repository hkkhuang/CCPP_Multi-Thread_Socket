
#ifndef _TCP_CONN_H
#define _TCP_CONN_H

#include "afos/AfSocket.h"
#include "afos/AfThread.h"

/* TcpConn:
   ��һ���߳���ά��Client - WorkingSocket֮���ͨ������
*/

class TcpConn : public AfThread
{
public:
	TcpConn(AfTcpSocket work_sock);
	~TcpConn();

private:
	virtual int ThreadMain(); //������д

private:
	AfTcpSocket m_WorkSock;
};




#endif

