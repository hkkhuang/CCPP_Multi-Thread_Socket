
#include "TcpHelper.h"
#include "afos/AfSocket.h"

int TcpHelper::WaitBytes(AfTcpSocket sock, 
						 void* buf, 
						 int count, 
						 int timeout)
{
	// ���ó�ʱ
	if(timeout > 0)
	{
		sock.SetOpt_RecvTimeout(timeout);
	}

	// ��������,ֱ������ָ�����ֽ���
	int bytes_got = 0;
	while(bytes_got < count)  //Recv �ӻ�����ȥ������ ȡ����������� ������Ҫ���͵��ֽ���  �������ȡ���ֹͣ  ��������,ֱ��ȥ���ƶ����ֽ���
	{
		int n = sock.Recv((char*)buf + bytes_got, count - bytes_got);
		if(n <= 0)
		{
			return bytes_got;
		}

		bytes_got += n;
	}

	return bytes_got;
}

