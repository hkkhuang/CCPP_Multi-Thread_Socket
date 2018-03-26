#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"

int main()
{
	printf("发送方: port=9000 ...\n");
	AfSockAddr local("127.0.0.1",9000);
	AfUdpSocket sock;
	if (sock.Open(local,false)<0)
	{
		printf("Socket无法正常创建！");
		return -1;
	}

	while (1)
	{
		//发送数据
		char buf[128];
		printf(">");
		gets_s(buf);

		int n = strlen(buf);

		// 发送
		AfSockAddr peer("127.0.0.1", 9001);
		sock.SendTo(buf, n, peer); //开始发送  参数（存储信息，信息长度，对方地址）

		//接收应答
		n = sock.RecvFrom(buf, 128, peer);
		buf[n] = 0;
		printf("收到回发应答：%s \n", buf);
		
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