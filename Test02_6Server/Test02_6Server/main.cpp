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
	if (sock.Open(local, false) < 0)
	{
		printf("无法创建socket! \n");
		return -1;
	}
	
	//设置接收超时时限
	//sock.SetOpt_RecvTimeout(3000);  //设置时限为3秒

	//设置为 非阻塞模式 non-blocked
	//sock.Ioctl_SetBlockedIo(false);  //默认是blocked方式

	while (1)
	{
		//unsigned char buf[128];
		char buf[128];
		AfSockAddr peer; // 对方的地址
		int n = sock.RecvFrom(buf, 128, peer); //参数  （用于存储接收信息空间，空间长度，对方地址）

		if (n <= 0)
		{
			break;
		}

		buf[n] = 0;
		printf("Got: %s \n", buf);


		//std::string peer_ip = peer.GetIp_str();
		//int port = peer.GetPort();
		//printf("From : %s:%d\n", peer_ip.c_str(), port);

		//回发
		strcat(buf, ".Over");
		sock.SendTo(buf,strlen(buf),peer);

		if (strcmp("bye", buf) == 0)
		{
			break; //结束
		}
	}

	// 关闭socket
	sock.Close();

	getchar();  //设置接收超时 则取消 不应用
	return 0;
}