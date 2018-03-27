#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include <string.h>

#include "afos/AfSocket.h"

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
	AfUdpSocket sock;
	sock.Open(local, true);

	FILE* fp = fopen("test_copy.pdf", "wb");
	unsigned char buf[1024 + 16];

	int count = 0;
	while (1)
	{
		AfSockAddr peer; // �Է��ĵ�ַ
		int n = sock.RecvFrom(buf, sizeof(buf), peer); //����  �����ڴ洢������Ϣ�ռ䣬�ռ䳤�ȣ��Է���ַ��

		if (n <= 0)
		{
			break;
		}

		//��� Ӧ�� ֻ�н��յ��ظ�Ӧ��֮����ܼ�������
		printf("Server send OK��\n");
		sock.SendTo("Ok", 2, peer);



		if (buf[0]==0x01)
		{
			printf("translate Start: \n");
		}
		else if (buf[0] == 0xFF)
		{
			printf("translate Finished \n");
			break;
		}
		else
		{
			//��������
			fwrite(buf + 16, 1, n - 16, fp);//buf+16����������
			printf("Got: %d bytes \n", n);
			printf("Packets = %d \n", ++count);
		}
	}

	fclose(fp);
	// �ر�socket
	sock.Close();

	getchar();  //���ý��ճ�ʱ ��ȡ�� ��Ӧ��
	return 0;
}