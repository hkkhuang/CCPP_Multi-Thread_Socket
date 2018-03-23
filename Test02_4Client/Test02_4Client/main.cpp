#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"
#include "Endian.h"

int main()
{
	printf("发送方: port=9000 ...\n");

	//创建socket
	AfSockAddr local("127.0.0.1", 9000);
	//AfSockAddr local("192.168.204.1", 9000);
	AfUdpSocket sock;
	sock.Open(local, true);

	while (1)
	{
		printf("Press Enter to send:");
		getchar();

		//发送数据
		//char buf[] = "hello";

		//发送一个整数
		unsigned int a = 0x12345678;
		unsigned char bytes[4];

		//转换为大端发送
		itob_32be(a, bytes);

		// 发送
		sock.SendTo(bytes, 4, AfSockAddr("127.0.0.1", 9001)); //开始发送  参数（存储信息，信息长度，对方地址）

		// 结束
		//if (strcmp("bye", buf) == 0)
		//{
		//	break;
		//}
	}

	// 关闭socket
	sock.Close();
	getchar();
	return 0;
}