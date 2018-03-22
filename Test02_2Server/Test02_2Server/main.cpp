#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include <string.h>

#include "afos/AfSocket.h"

/* UDP socket ����
���շ�: 9001
*/

int main()
{
	printf("���շ�: port=9001 ...\n");

	AfSockAddr local("127.0.0.1", 9001);
	//AfSockAddr local("192.168.204.129", 9001);
	AfUdpSocket sock;
	sock.Open(local, true);

	while (1)
	{
		char buf[128];
		AfSockAddr peer; // �Է��ĵ�ַ
		int n = sock.RecvFrom(buf, 128, peer);

		if (n <= 0)
		{
			break;
		}

		buf[n] = 0;
		printf("Got: %s \n", buf);

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