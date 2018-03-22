#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"

int main()
{
	printf("发送方: port=9000 ...\n");

	AfSockAddr local("127.0.0.1", 9000);
	//AfSockAddr local("192.168.204.1", 9000);
	AfUdpSocket sock;
	sock.Open(local, true);


	if (1)
	{
		//设置SendBuf的大小
		int bufsize = 128 * 1024;//128K
		int ret = setsockopt(sock.hSock, SOL_SOCKET, SO_SNDBUF, (const char*)&bufsize, sizeof(int));

		if (ret < 0)
		{
			//设置失败；
		}
	}
	while (1)
	{
		// 让用户输入一段文本
		char buf[128];
		printf("> ");
		gets_s(buf);
		int n = strlen(buf);

		// 发送
		AfSockAddr peer("127.0.0.1", 9001); // 对方地址
		//AfSockAddr peer("192.168.204.129", 9001); // 对方地址
		
		sock.SendTo(buf, n, peer);

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