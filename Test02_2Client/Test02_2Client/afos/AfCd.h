
#ifndef _AF_CD_H
#define _AF_CD_H

/* AfCd
   �������ý��̵�"��ǰĿ¼"

   ���ߣ��۷�
   �汾��2016-01-05
   ���°汾���ڹ��� http://afanihao.cn �ϻ�ȡ
*/

#include <string>
using std::string;

class AfCd
{
public:
	// �õ�exe�ļ����ڵ�Ŀ¼ 
	static string exeLocation(char seperator='\\');

	// �л���Ŀ��λ�� 
	static void cd(const string& targetDir);

	// �л���exe���е�λ�� 
	static void cd();
};

#endif

