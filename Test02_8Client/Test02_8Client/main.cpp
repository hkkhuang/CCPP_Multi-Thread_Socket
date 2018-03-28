#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"
#include "afos/AfThread.h"


int main()
{
	//创建Socket 
	AfTcpSocket client_sock;
	client_sock.Open();

	//连接服务器
	AfSockAddr server_addr("127.0.0.1", 10000);
	if (client_sock.Connect(server_addr) < 0)
	{
		printf("无法连接服务器！\n");
		return -1;
	}

	char buf[1024];

	//发送请求
	strcpy(buf, "hello,server");
	int n = strlen(buf);
	client_sock.Send(buf, n);

	//接受应答
	n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0;
	printf("Got:%s\n", buf);

	getchar();
	return 0;
}