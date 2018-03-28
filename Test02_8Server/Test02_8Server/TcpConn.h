#pragma once
#include "afos/AfThread.h"
#include "afos/AfSocket.h"

//TcpConn 用一个线程维护Client-WorkingSocket之间的通话连接
class TcpConn :public AfThread
{
public:
	TcpConn(AfTcpSocket work_sock);
	~TcpConn();
private:
	virtual int ThreadMain();

private:
	AfTcpSocket m_WorkSock;
};