#ifndef _AF_FINE_CLOCK_H
#define _AF_FINE_CLOCK_H


/* AfFineClock
    ���뼶ʱ��

	����  �۷�
	����  http://afanihao.cn
	�汾��2016-01-05
	�˴����� C/C++ѧϰָ�ϣ�����ƪ��-Windows API �Ĺٷ����룬���°汾�뵽��������
   
*/


class AfFineClock
{
public:
	AfFineClock();

	// ���ص�ǰʱ��(��0��ʼ,��λ����)
	unsigned int now();

	// ����ʱ�ӣ�����������һ������������ʱ�䳤��
	unsigned int reset();

private:
	unsigned int m_startPoint;
};

#endif

