#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"

int main()
{
	printf("发送方: port=9000 ...\n");
	//printf("发送方: port未指定，OS自动分配\n");
	AfSockAddr local("127.0.0.1", 9000);
	//创建socket 不知道本地IP地址和端口号
	AfUdpSocket sock;
	//sock.Open();
	if (sock.Open(local,false)<0)
	{
		printf("Socket无法正常创建！");
		return -1;
	}

	while (1)
	{
		//送数据
		char buf[128];
		printf(">");
		gets_s(buf);

		int n = strlen(buf);

		// 发送
		AfSockAddr peer("127.0.0.1", 9001);
		//sock.SendTo(buf, n, AfSockAddr("127.0.0.1", 9001)); //开始发送  参数（存储信息，信息长度，对方地址）
		sock.SendTo(buf, n, peer); //开始发送  参数（存储信息，信息长度，对方地址）

		//查看OS自动分配的端口号是多少
// 		AfSockAddr local;
// 		sock.GetLocalAddr(local);
// 		unsigned int port = local.GetPort();
// 		printf("local port:%d \n", port);
		
		// 结束
		if (strcmp("bye", buf) == 0)
		{
			break;
		}
	}

	// 关闭socket
	sock.Close();
	getchar();
	return 0;
}