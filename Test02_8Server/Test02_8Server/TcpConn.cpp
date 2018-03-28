#include <stdio.h>
#include <string.h>
#include "TcpConn.h"

TcpConn::TcpConn(AfTcpSocket work_sock)
{
	m_WorkSock = work_sock;
}

TcpConn::~TcpConn()
{

}

int TcpConn::ThreadMain()
{
	//ΪClient�ṩ����
	char buf[1024];

	//���տͻ�����
	int n = m_WorkSock.Recv(buf, 1024);
	buf[n] = 0;
	printf("�ͻ�����%s\n", buf);

	//Ӧ��ͻ�
	strcpy(buf, "Ok,Client");
	n = strlen(buf);
	m_WorkSock.Send(buf, n);

	//�ر�
	m_WorkSock.Close();
	return 0;
}