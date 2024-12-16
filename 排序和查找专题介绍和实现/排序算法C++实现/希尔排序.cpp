#include<iostream>
using namespace std;

const int INCRGAP = 3;
void ShellSort(int a[], int len)
{
	
	int insertNum = 0;
	unsigned gap = len / INCRGAP + 1; // ������ʼ��,ע�������len<INCRGAPʱ��gapΪ0������Ϊ�˱�֤����ѭ����gap����Ϊ1������
	while (gap) // while gap>=1
	{
		for (unsigned i = gap; i < len; i++) // ���飬��ÿ���������н��в�������
		{
			insertNum = a[i];//����ǰ��Ԫ��ֵ�ȴ���������������
			unsigned j = i;
			while (j >= gap && insertNum < a[j - gap])//Ѱ�Ҳ���λ��
			{
				a[j] = a[j - gap];
				j -= gap;
			}
			a[j] = insertNum;
		}
		gap = gap / INCRGAP;
	}




}
int main05()
{

	int A[] = { 6, 5, 3, 1, 8, 7, 2, 4 };// ��С�����������
	int n = sizeof(A) / sizeof(int);
	ShellSort(A, n);
	printf("ϣ����������");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
	system("pause");

	return 0;
}