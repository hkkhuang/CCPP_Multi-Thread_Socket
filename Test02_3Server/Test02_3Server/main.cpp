#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include <string.h>

#include "afos/AfSocket.h"

/* UDP socket 测试
接收方: 9001
*/

///按照十六进制方式输出
void print_bytes(void* buf, int n)
{
	unsigned char* bytes = (unsigned char*)buf;

	for (int i=0;i<n;i++)
	{
		printf("%02X ", bytes[i]);
	}
	printf("\n");
}

int main()
{
	printf("接收方: port=9001 ...\n");

	AfSockAddr local("127.0.0.1", 9001);
	//AfSockAddr local("192.168.204.129", 9001);
	AfUdpSocket sock;
	sock.Open(local, true);
	
	while (1)
	{
		char buf[128];
		AfSockAddr peer; // 对方的地址
		int n = sock.RecvFrom(buf, 128, peer); //参数  （用于存储接收信息空间，空间长度，对方地址）

		if (n <= 0)
		{
			break;
		}

		//buf[n] = 0;
		//printf("Got: %s \n", buf);

		printf("Got: ");
		print_bytes(buf, n);
		

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