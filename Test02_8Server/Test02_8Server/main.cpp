#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include <string.h>

#include "afos/AfSocket.h"
#include "TcpConn.h"

int main()
{
	//创建Socket
	AfTcpSocket server_sock;
	//1.占用端口号
	server_sock.Open(AfSockAddr(10000), true); 
	//2.开始监听
	server_sock.Listen();

	while (1)
	{
		AfTcpSocket work_sock;
		//Accept
		if (server_sock.Accept(&work_sock)<0)
		{
			break;
		}

		//新建一个线程，处理client的请求  总机接受客户请求 交给一个客服人员处理
		TcpConn* conn = new TcpConn(work_sock);
		conn->Run();
	}


	getchar();
	return 0;
}