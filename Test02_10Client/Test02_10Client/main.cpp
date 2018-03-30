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
	strcpy(buf, "hello,server");
	int n = strlen(buf);
	client_sock.Send(buf, n);

	//select
	printf("wait....\n");
	//int ret = client_sock.Select_ForReading(1000);//select ��ȡ ��ѯ�Ƿ�ɶ�   Ҳ���Ƿ�����������Ϣ  ���ó�ʱʱ��
	//int ret = client_sock.Select_ForReading(3000);//select ��ȡ ��ѯ�Ƿ�ɶ�   Ҳ���Ƿ�����������Ϣ  ���ó�ʱʱ��
	int ret = client_sock.Select_ForReading(6000);//select ��ȡ ��ѯ�Ƿ�ɶ�   Ҳ���Ƿ�����������Ϣ  ���ó�ʱʱ��
	printf("ret: %d \n", ret);
	

	//Client����Ӧ��
	n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0; //���յ��ֽ��� ����buf�Ľ���λ��
	printf("Got:%s\n", buf);

	getchar();
	return 0;
}