#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"
#include "Endian.h"

int main()
{
	printf("���ͷ�: port=9000 ...\n");

	//����socket
	AfSockAddr local("127.0.0.1", 9000);
	//AfSockAddr local("192.168.204.1", 9000);
	AfUdpSocket sock;
	sock.Open(local, true);

	while (1)
	{
		printf("Press Enter to send:");
		getchar();

		//��������
		//char buf[] = "hello";

		//����һ������
		unsigned int a = 0x12345678;
		unsigned char bytes[4];

		//ת��Ϊ��˷���
		itob_32be(a, bytes);

		// ����
		sock.SendTo(bytes, 4, AfSockAddr("127.0.0.1", 9001)); //��ʼ����  �������洢��Ϣ����Ϣ���ȣ��Է���ַ��

		// ����
		//if (strcmp("bye", buf) == 0)
		//{
		//	break;
		//}
	}

	// �ر�socket
	sock.Close();
	getchar();
	return 0;
}