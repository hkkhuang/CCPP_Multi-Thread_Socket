
#include <stdio.h>
#include <string.h>
#include "TcpConn.h"
#include "TcpHelper.h"

//���캯��
TcpConn::TcpConn(AfTcpSocket work_sock)
{
	m_WorkSock = work_sock;
}
//��������
TcpConn::~TcpConn()
{

}

//������δ���
int TcpConn::ThreadMain()
{
	// Ϊclient�ṩ����
	unsigned char buf[1024];
	int n ;

	// ���տͻ�������
	n = m_WorkSock.Recv(buf, 1023);
	buf[n] = 0;
	printf("�ͻ�����: %s \n", buf);
	
	//���÷�������ʱ
	AfThread::Msleep(5000);

	// Ӧ��ͻ�
	m_WorkSock.Send("yes", 3);

	// �ر�socket
	m_WorkSock.Close();
	
	return 0;
}

