#include <stdio.h>
#include <string.h>
#include "TcpConn.h"

TcpConn::TcpConn(AfTcpSocket work_sock)
{
	m_WorkSock = work_sock;
}

TcpConn::~TcpConn()
{

}

int TcpConn::ThreadMain()
{
	//为Client提供服务
	char buf[1024];

	//接收客户请求
	int n = m_WorkSock.Recv(buf, 1024);
	buf[n] = 0;
	printf("客户请求：%s\n", buf);

	//应答客户
	strcpy(buf, "Ok,Client");
	n = strlen(buf);
	m_WorkSock.Send(buf, n);

	//关闭
	m_WorkSock.Close();
	return 0;
}