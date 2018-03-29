
#include <stdio.h>
#include <string.h>

#include "TcpConn.h"
#include "Endian.h"
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

	//配合演示Client阻塞  先不接收
	//AfThread::Msleep(100000);

	//先接受 数据长度
	//m_WorkSock.Recv(buf, 2);
	//unsigned short count = btoi_16be(buf);


	// 接收客户的请求
	//n = m_WorkSock.Recv(buf, 1023);
	//buf[n] = 0;
	//printf("客户请求: %s \n", buf);
	
	// 使用边界
	TcpHelper::WaitBytes(m_WorkSock, buf, 2);
	unsigned short count = btoi_16be(buf);
	n = TcpHelper::WaitBytes(m_WorkSock, buf, count);
	buf[n] = 0;
	printf("客户请求: %s \n", buf);

	// 应答客户
	m_WorkSock.Send("yes", 3);

	// 关闭socket
	m_WorkSock.Close();
	
	return 0;
}

