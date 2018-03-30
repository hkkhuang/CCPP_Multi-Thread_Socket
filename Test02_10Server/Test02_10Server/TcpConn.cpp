
#include <stdio.h>
#include <string.h>
#include "TcpConn.h"
#include "TcpHelper.h"

//构造函数
TcpConn::TcpConn(AfTcpSocket work_sock)
{
	m_WorkSock = work_sock;
}
//析构函数
TcpConn::~TcpConn()
{

}

//具体如何处理
int TcpConn::ThreadMain()
{
	// 为client提供服务
	unsigned char buf[1024];
	int n ;

	// 接收客户的请求
	n = m_WorkSock.Recv(buf, 1023);
	buf[n] = 0;
	printf("客户请求: %s \n", buf);
	
	//设置服务器超时
	AfThread::Msleep(5000);

	// 应答客户
	m_WorkSock.Send("yes", 3);

	// 关闭socket
	m_WorkSock.Close();
	
	return 0;
}

