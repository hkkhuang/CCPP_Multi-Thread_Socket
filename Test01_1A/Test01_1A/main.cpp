#include <stdio.h>
#include <stdlib.h>

//�����100��
void Buddhist()
{
	for (int i = 0; i < 100; i++)
	{
		printf("�����������\n");
	}
}

//��Ŷ���500��
void Confucian()
{
	for (int i = 0; i < 500; i++)
	{
		printf("��Ŷ��顣����\n");
	}
}

int main()
{
	//����ʵ�� �������  ���е���
	Buddhist();
	Confucian();

	system("Pause");
	return 0;
}