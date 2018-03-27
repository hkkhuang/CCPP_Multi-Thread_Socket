#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afos/AfSocket.h"
#include "afos/AfThread.h"

int main()
{
	printf("���ͷ�: port=9000 ...\n");
	AfUdpSocket sock; //����socket
	sock.Open();

	printf("press Enter to send\n");
	getchar();

	FILE* fp = fopen("test.pdf", "rb");
	unsigned char buf[1024 + 16];//�ֿ鴫�� һ��1024�ֽڣ�16 ��ʾ״̬

	AfSockAddr peer("127.0.0.1", 9001); //���յ�ַ

	//����ָ��  ��ʼ����
	buf[0] = 0x01;
	sock.SendTo(buf, 16, peer);

	int count = 0;
	while (1)
	{
		int n = fread(buf + 16, 1, 1024, fp); //��ȡ�ļ��ŵ�buf[16]���Ժ��λ��
		if (n <= 0)
		{
			break;
		}

		//���ݰ�
		buf[0] = 0x02;
		sock.SendTo(buf, n + 16, peer);

		//ͨ��Ӧ��ģʽ���ƽ���
		//AfThread::Msleep(50);//���ⷢ��̫��  ���Ͷ˿��Ʒ��ͽ��� ����������ɰ���ʧ
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

	//����ָ�� ��������
	buf[0] = 0xFF;
	sock.SendTo(buf, 16, peer);

	printf("send finished! press enter to continue \n");
	getchar();

	fclose(fp);//�ر��ļ�

	// �ر�socket
	sock.Close();
	getchar();
	return 0;
}