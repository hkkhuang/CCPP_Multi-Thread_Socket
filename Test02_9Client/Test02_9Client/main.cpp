#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Endian.h"
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
// 	strcpy(buf, "hello,server");
// 	int n = strlen(buf);
// 	client_sock.Send(buf, n);

	//Client端发送信息
// 	client_sock.Send("hello", 5);
// 	client_sock.Send("world", 5);

	//使用边界定义 先发送需要发送的数据长度 再发送数据
	unsigned char bytes[2];
	itob_16be(10, bytes);
	client_sock.Send(bytes, 2);
	client_sock.Send("helloworld", 10);

	//演示阻塞 Send()阻塞
// 	for (int i=0;i<256;i++)
// 	{
// 		printf("send # %d...\n", i + 1);
// 		client_sock.Send(buf, 1024);
// 		printf("OK!\n");
// 	}

	//Client接受应答
	int n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0; //接收到字节数 设置buf的结束位置
	printf("Got:%s\n", buf);

	getchar();
	return 0;
}