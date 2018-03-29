
#include <stdio.h>
#include <string.h>

#include "TcpConn.h"
#include "Endian.h"
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

	//�����ʾClient����  �Ȳ�����
	//AfThread::Msleep(100000);

	//�Ƚ��� ���ݳ���
	//m_WorkSock.Recv(buf, 2);
	//unsigned short count = btoi_16be(buf);


	// ���տͻ�������
	//n = m_WorkSock.Recv(buf, 1023);
	//buf[n] = 0;
	//printf("�ͻ�����: %s \n", buf);
	
	// ʹ�ñ߽�
	TcpHelper::WaitBytes(m_WorkSock, buf, 2);
	unsigned short count = btoi_16be(buf);
	n = TcpHelper::WaitBytes(m_WorkSock, buf, count);
	buf[n] = 0;
	printf("�ͻ�����: %s \n", buf);

	// Ӧ��ͻ�
	m_WorkSock.Send("yes", 3);

	// �ر�socket
	m_WorkSock.Close();
	
	return 0;
}

