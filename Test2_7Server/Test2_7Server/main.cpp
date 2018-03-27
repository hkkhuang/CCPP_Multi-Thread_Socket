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
	AfUdpSocket sock;
	sock.Open(local, true);

	FILE* fp = fopen("test_copy.pdf", "wb");
	unsigned char buf[1024 + 16];

	int count = 0;
	while (1)
	{
		AfSockAddr peer; // 对方的地址
		int n = sock.RecvFrom(buf, sizeof(buf), peer); //参数  （用于存储接收信息空间，空间长度，对方地址）

		if (n <= 0)
		{
			break;
		}

		//添加 应答 只有接收到回复应答之后才能继续发送
		printf("Server send OK。\n");
		sock.SendTo("Ok", 2, peer);



		if (buf[0]==0x01)
		{
			printf("translate Start: \n");
		}
		else if (buf[0] == 0xFF)
		{
			printf("translate Finished \n");
			break;
		}
		else
		{
			//接收数据
			fwrite(buf + 16, 1, n - 16, fp);//buf+16后面是数据
			printf("Got: %d bytes \n", n);
			printf("Packets = %d \n", ++count);
		}
	}

	fclose(fp);
	// 关闭socket
	sock.Close();

	getchar();  //设置接收超时 则取消 不应用
	return 0;
}