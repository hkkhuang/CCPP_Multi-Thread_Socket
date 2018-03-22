#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include <string.h>

#include "afos/AfSocket.h"

/* UDP socket 测试
接收方: 9001
*/

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
		int n = sock.RecvFrom(buf, 128, peer);

		if (n <= 0)
		{
			break;
		}

		buf[n] = 0;
		printf("Got: %s \n", buf);

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