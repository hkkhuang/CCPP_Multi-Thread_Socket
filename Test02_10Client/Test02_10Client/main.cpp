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

	if (0)
	{
		//获取Sendbuf大小
		int bufsize = 0; //8K
		socklen_t len = 4;
		int ret = getsockopt(client_sock.hSock, SOL_SOCKET, SO_SNDBUF, (char*)&bufsize, &len);
		printf("缓冲区大小:%d!\n", bufsize);
		if (ret < 0)
		{
			//设置失败
			printf("failed to get option!\n");
		}
	}

	if (0)
	{
		//设置SendBuf的大小  
		//在TCP里面设置缓冲区大小是有用的
		int bufsize = 128 * 1024;
		int ret = setsockopt(client_sock.hSock, SOL_SOCKET, SO_SNDBUF, (const char*)&bufsize, sizeof(int));
		if (ret<0)
		{
			//设置失败
		}
	}
	
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

	//select
	printf("wait....\n");
	//int ret = client_sock.Select_ForReading(1000);//select 读取 查询是否可读   也就是服务器发回信息  设置超时时间
	//int ret = client_sock.Select_ForReading(3000);//select 读取 查询是否可读   也就是服务器发回信息  设置超时时间
	int ret = client_sock.Select_ForReading(6000);//select 读取 查询是否可读   也就是服务器发回信息  设置超时时间
	printf("ret: %d \n", ret);
	

	//Client接受应答
	n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0; //接收到字节数 设置buf的结束位置
	printf("Got:%s\n", buf);

	getchar();
	return 0;
}