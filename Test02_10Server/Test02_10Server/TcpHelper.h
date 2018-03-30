#ifndef _TCP_HELPER_H
#define _TCP_HELPER_H

#include "afos/AfSocket.h"

class TcpHelper
{

public:
	// 接收指定长度的字节数据
	// count: 准备接收多少字节
	// timeout: 如果为0，表示阻塞等待，否则，表示设置接收超时
	static int WaitBytes(AfTcpSocket sock, 
		void* buf, 
		int count, 
		int timeout=0);
};




#endif


