#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include <string.h>

#include "afos/AfSocket.h"
#include "TcpConn.h"

int main()
{
	//����Socket
	AfTcpSocket server_sock;
	//1.ռ�ö˿ں�
	server_sock.Open(AfSockAddr(10000), true); 
	//2.��ʼ����
	server_sock.Listen();

	while (1)
	{
		AfTcpSocket work_sock;
		//Accept
		if (server_sock.Accept(&work_sock)<0)
		{
			break;
		}

		//�½�һ���̣߳�����client������  �ܻ����ܿͻ����� ����һ���ͷ���Ա����
		TcpConn* conn = new TcpConn(work_sock);
		conn->Run();
	}


	getchar();
	return 0;
}