#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include <string.h>

#include "afos/AfSocket.h"
#include "Endian.h"

/* UDP socket ����
���շ�: 9001
*/

///����ʮ�����Ʒ�ʽ���
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
	printf("���շ�: port=9001 ...\n");

	AfSockAddr local("127.0.0.1", 9001);
	//AfSockAddr local("192.168.204.129", 9001);
	AfUdpSocket sock;
	sock.Open(local, true);
	
	while (1)
	{
		unsigned char buf[128];
		AfSockAddr peer; // �Է��ĵ�ַ
		int n = sock.RecvFrom(buf, 128, peer); //����  �����ڴ洢������Ϣ�ռ䣬�ռ䳤�ȣ��Է���ַ��

		if (n <= 0)
		{
			break;
		}


		//�����ֽ�������յ�����
		printf("Got: ");
		print_bytes(buf, n);

		unsigned int a = btoi_32be(buf);
		printf("Got a number: %08x \n", a);
		
	}

	// �ر�socket
	sock.Close();

	getchar();
	return 0;
}