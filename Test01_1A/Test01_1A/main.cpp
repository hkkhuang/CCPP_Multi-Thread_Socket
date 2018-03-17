#include <stdio.h>
#include <stdlib.h>

//和尚念经100遍
void Buddhist()
{
	for (int i = 0; i < 100; i++)
	{
		printf("和尚念经。。。\n");
	}
}

//秀才读书500遍
void Confucian()
{
	for (int i = 0; i < 500; i++)
	{
		printf("秀才读书。。。\n");
	}
}

int main()
{
	//函数实现 依次完成  串行调用
	Buddhist();
	Confucian();

	system("Pause");
	return 0;
}