#ifndef _AF_FINE_CLOCK_H
#define _AF_FINE_CLOCK_H


/* AfFineClock
    毫秒级时钟

	作者  邵发
	官网  http://afanihao.cn
	版本：2016-01-05
	此代码是 C/C++学习指南（补充篇）-Windows API 的官方代码，最新版本请到官网下载
   
*/


class AfFineClock
{
public:
	AfFineClock();

	// 返回当前时间(从0开始,单位毫秒)
	unsigned int now();

	// 重置时钟，并返回自上一次重置以来的时间长度
	unsigned int reset();

private:
	unsigned int m_startPoint;
};

#endif

