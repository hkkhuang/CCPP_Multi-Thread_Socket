
#ifndef _AF_CD_H
#define _AF_CD_H

/* AfCd
   用于设置进程的"当前目录"

   作者：邵发
   版本：2016-01-05
   最新版本请在官网 http://afanihao.cn 上获取
*/

#include <string>
using std::string;

class AfCd
{
public:
	// 得到exe文件所在的目录 
	static string exeLocation(char seperator='\\');

	// 切换到目标位置 
	static void cd(const string& targetDir);

	// 切换到exe所有的位置 
	static void cd();
};

#endif

