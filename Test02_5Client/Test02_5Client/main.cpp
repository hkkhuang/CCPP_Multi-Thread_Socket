#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"

int main()
{
	printf("���ͷ�: port=9000 ...\n");
	//printf("���ͷ�: portδָ����OS�Զ�����\n");
	AfSockAddr local("127.0.0.1", 9000);
	//����socket ��֪������IP��ַ�Ͷ˿ں�
	AfUdpSocket sock;
	//sock.Open();
	if (sock.Open(local,false)<0)
	{
		printf("Socket�޷�����������");
		return -1;
	}

	while (1)
	{
		//������
		char buf[128];
		printf(">");
		gets_s(buf);

		int n = strlen(buf);

		// ����
		AfSockAddr peer("127.0.0.1", 9001);
		//sock.SendTo(buf, n, AfSockAddr("127.0.0.1", 9001)); //��ʼ����  �������洢��Ϣ����Ϣ���ȣ��Է���ַ��
		sock.SendTo(buf, n, peer); //��ʼ����  �������洢��Ϣ����Ϣ���ȣ��Է���ַ��

		//�鿴OS�Զ�����Ķ˿ں��Ƕ���
// 		AfSockAddr local;
// 		sock.GetLocalAddr(local);
// 		unsigned int port = local.GetPort();
// 		printf("local port:%d \n", port);
		
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