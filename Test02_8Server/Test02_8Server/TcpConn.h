#pragma once
#include "afos/AfThread.h"
#include "afos/AfSocket.h"

//TcpConn ��һ���߳�ά��Client-WorkingSocket֮���ͨ������
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