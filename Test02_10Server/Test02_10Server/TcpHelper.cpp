
#include "TcpHelper.h"
#include "afos/AfSocket.h"

int TcpHelper::WaitBytes(AfTcpSocket sock, 
						 void* buf, 
						 int count, 
						 int timeout)
{
	// 设置超时
	if(timeout > 0)
	{
		sock.SetOpt_RecvTimeout(timeout);
	}

	// 反复接收,直到接满指定的字节数
	int bytes_got = 0;
	while(bytes_got < count)  //Recv 从缓冲器去除数据 取出多少算多少 我们有要发送的字节数  则可以在取完后停止  反复接收,直到去满制定的字节数
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

