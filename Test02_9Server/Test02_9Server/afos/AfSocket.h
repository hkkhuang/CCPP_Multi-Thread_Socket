
#ifndef _AF_SOCKET_H
#define _AF_SOCKET_H

#include <string>


#ifdef _WIN32
// windows 下的socket定义
#include <winsock2.h>
#include <ws2tcpip.h>

typedef SOCKET socket_t;

#define socket_open socket
#define socket_close closesocket
#define socket_ioctl  ioctlsocket
#else
// linux下的socket定义
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
typedef int socket_t;

#define socket_open socket
#define socket_close close
#define socket_ioctl  ioctl
#endif

#define socket_accept  accept
#define socket_bind      bind
#define socket_connect connect
#define socket_listen    listen
#define socket_send     send
#define socket_recv      recv
#define socket_sendto   sendto
#define socket_recvfrom recvfrom
#define socket_select    select
#define socket_setsockopt setsockopt
#define socket_getsockopt getsockopt

/* OS_Socket:
	*) 这是一个简单类，用户可以直接赋值传递
	*) 用户应该显式的关闭Close()，在析构函数里不会自动关闭
	*) 用户可以直接操作socket handle: hSock
*/

/* 可以直接强转成sockaddr_in结构*/
class AfSockAddr
{
public:
	explicit AfSockAddr();
	explicit AfSockAddr(const char* ip, unsigned short port);
	explicit AfSockAddr(const char* ip); // 默认端口为0
	explicit AfSockAddr(unsigned short port); // 默认IP为0.0.0.0
	explicit AfSockAddr(sockaddr_in addr);

	void SetIp(const char* ip);
	void SetIp(unsigned int ip);
	void SetPort(unsigned short port);

	std::string GetIp_str() const;
	unsigned int GetIp_n() const;
	unsigned short GetPort() const;

public:
	sockaddr_in iAddr;
};

class AfSocket
{
public:
	AfSocket(); 

	// ms=0时永不超时, 单位ms, ms=1可以认为是立即返回(1ms很快完成)
	int SetOpt_RecvTimeout(int ms); 
	int SetOpt_SendTimeout(int ms);
	int GetOpt_RecvTimeout(); 
	int GetOpt_SendTimeout();

	int Ioctl_SetBlockedIo(bool blocked);
	int SetOpt_ReuseAddr(bool reuse);

	int GetPeerAddr(AfSockAddr& addr) const;
	int GetLocalAddr(AfSockAddr& addr) const;

	// select机制:查询读写状态
	// 返回值: >0，表示可以读或写 =0表示超时，<0表示socket不可用
	int Select_ForReading(int timeout);
	int Select_ForWriting(int timeout);

public:
	socket_t hSock; // 可以直接访问这个handle
};

class AfTcpSocket : public AfSocket
{
public:
	int Open(bool resue = false);
	int Open(const AfSockAddr& addr , bool reuse = false);

	void Close();

	// 服务器
	int Listen(int backlog = 16);
	int Accept(AfTcpSocket* peer);
	
	// 客户端
	int Connect(const AfSockAddr& addr);

	// 发送接收
	int Send(const void* buf, int len);
	int Recv(void* buf, int len, int waitall=0);

};

class AfUdpSocket : public AfSocket
{
public:
	int Open(bool resue = false);
	int Open(const AfSockAddr& addr,  bool reuse = false);

	void Close();

	int SendTo(const void* buf, int len, const AfSockAddr&  peers);
	int RecvFrom( void* buf, int max_len, AfSockAddr& peer);
};

class AfMcastSocket : public AfSocket
{
public:
	int Open(const char* mcast_ip, int port, const char* local_ip);
	void Close();

	/* 发送多播时，使用普通UdpSock + 多播路由即可 */
	//int SendTo(const void* buf, int len, const OS_SockAddr& peer);
	int RecvFrom( void* buf, int max_len, AfSockAddr& peer);

private:
	ip_mreq m_McReq;
};

#endif


