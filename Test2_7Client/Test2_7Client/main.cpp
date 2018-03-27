#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"
#include "afos/AfThread.h"

int main()
{
	printf("发送方: port=9000 ...\n");
	AfUdpSocket sock; //创建socket
	sock.Open();

	printf("press Enter to send\n");
	getchar();

	FILE* fp = fopen("test.pdf", "rb");
	unsigned char buf[1024 + 16];//分块传输 一次1024字节，16 表示状态

	AfSockAddr peer("127.0.0.1", 9001); //接收地址

	//设置指令  开始传输
	buf[0] = 0x01;
	sock.SendTo(buf, 16, peer);

	int count = 0;
	while (1)
	{
		int n = fread(buf + 16, 1, 1024, fp); //读取文件放到buf[16]及以后的位置
		if (n <= 0)
		{
			break;
		}

		//数据包
		buf[0] = 0x02;
		sock.SendTo(buf, n + 16, peer);

		//通过应发模式控制节奏
		//AfThread::Msleep(50);//避免发送太快  发送端控制发送节奏 否则容易造成包丢失
		char buf_server[16];
		int m=sock.RecvFrom(buf_server, 16, peer);
		buf_server[m]=0;
		
		if (strcmp("Ok", buf_server) == 0)
		{
			printf("Receive: %s \n", buf_server);
		}
		else
		{
			break;
		}

		

		printf("send packets: count=%d\n", ++count);
	}

	//设置指令 结束发送
	buf[0] = 0xFF;
	sock.SendTo(buf, 16, peer);

	printf("send finished! press enter to continue \n");
	getchar();

	fclose(fp);//关闭文件

	// 关闭socket
	sock.Close();
	getchar();
	return 0;
}