#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"

int main()
{
	printf("���ͷ�: port=9000 ...\n");

	AfSockAddr local("127.0.0.1", 9000);
	//AfSockAddr local("192.168.204.1", 9000);
	AfUdpSocket sock;
	sock.Open(local, true);


	if (1)
	{
		//����SendBuf�Ĵ�С
		int bufsize = 128 * 1024;//128K
		int ret = setsockopt(sock.hSock, SOL_SOCKET, SO_SNDBUF, (const char*)&bufsize, sizeof(int));

		if (ret < 0)
		{
			//����ʧ�ܣ�
		}
	}
	while (1)
	{
		// ���û�����һ���ı�
		char buf[128];
		printf("> ");
		gets_s(buf);
		int n = strlen(buf);

		// ����
		AfSockAddr peer("127.0.0.1", 9001); // �Է���ַ
		//AfSockAddr peer("192.168.204.129", 9001); // �Է���ַ
		
		sock.SendTo(buf, n, peer);

		// ����
		if (strcmp("bye", buf) == 0)
		{
			break;
		}
	}

	// �ر�socket
	sock.Close();
	getchar();
	return 0;
}