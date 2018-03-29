#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Endian.h"
#include "afos/AfSocket.h"
#include "afos/AfThread.h"


int main()
{
	//����Socket 
	AfTcpSocket client_sock;
	client_sock.Open();

	if (0)
	{
		//��ȡSendbuf��С
		int bufsize = 0; //8K
		socklen_t len = 4;
		int ret = getsockopt(client_sock.hSock, SOL_SOCKET, SO_SNDBUF, (char*)&bufsize, &len);
		printf("��������С:%d!\n", bufsize);
		if (ret < 0)
		{
			//����ʧ��
			printf("failed to get option!\n");
		}
	}

	if (0)
	{
		//����SendBuf�Ĵ�С  
		//��TCP�������û�������С�����õ�
		int bufsize = 128 * 1024;
		int ret = setsockopt(client_sock.hSock, SOL_SOCKET, SO_SNDBUF, (const char*)&bufsize, sizeof(int));
		if (ret<0)
		{
			//����ʧ��
		}
	}
	
	//���ӷ�����
	AfSockAddr server_addr("127.0.0.1", 10000);
	if (client_sock.Connect(server_addr) < 0)
	{
		printf("�޷����ӷ�������\n");
		return -1;
	}

	char buf[1024];

	//��������
// 	strcpy(buf, "hello,server");
// 	int n = strlen(buf);
// 	client_sock.Send(buf, n);

	//Client�˷�����Ϣ
// 	client_sock.Send("hello", 5);
// 	client_sock.Send("world", 5);

	//ʹ�ñ߽綨�� �ȷ�����Ҫ���͵����ݳ��� �ٷ�������
	unsigned char bytes[2];
	itob_16be(10, bytes);
	client_sock.Send(bytes, 2);
	client_sock.Send("helloworld", 10);

	//��ʾ���� Send()����
// 	for (int i=0;i<256;i++)
// 	{
// 		printf("send # %d...\n", i + 1);
// 		client_sock.Send(buf, 1024);
// 		printf("OK!\n");
// 	}

	//Client����Ӧ��
	int n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0; //���յ��ֽ��� ����buf�Ľ���λ��
	printf("Got:%s\n", buf);

	getchar();
	return 0;
}