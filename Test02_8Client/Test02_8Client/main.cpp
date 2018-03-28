#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"
#include "afos/AfThread.h"


int main()
{
	//����Socket 
	AfTcpSocket client_sock;
	client_sock.Open();

	//���ӷ�����
	AfSockAddr server_addr("127.0.0.1", 10000);
	if (client_sock.Connect(server_addr) < 0)
	{
		printf("�޷����ӷ�������\n");
		return -1;
	}

	char buf[1024];

	//��������
	strcpy(buf, "hello,server");
	int n = strlen(buf);
	client_sock.Send(buf, n);

	//����Ӧ��
	n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0;
	printf("Got:%s\n", buf);

	getchar();
	return 0;
}