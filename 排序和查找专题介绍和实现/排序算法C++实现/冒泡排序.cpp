/* https://www.cnblogs.com/eniac12/p/5329396.html */

#include<iostream>
using namespace std;

void Swap(int A[], int i, int j)
{
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}
void BubbleSort(int A[], int n)
{
	for (int j = 0; j < n - 1; j++)         // ÿ�����Ԫ�ؾ�������һ��"��"����������
	{
		for (int i = 0; i < n - 1 - j; i++) // ���αȽ����ڵ�����Ԫ��,ʹ�ϴ���Ǹ������
		{
			if (A[i] > A[i + 1])            // ��������ĳ�A[i] >= A[i + 1],���Ϊ���ȶ��������㷨
			{
				Swap(A, i, i + 1);
			}
		}
	}
}
int main01() {

	int A[] = { 6, 5, 3, 1, 8, 7, 2, 4 };    // ��С����ð������
	int n = sizeof(A) / sizeof(int);
	BubbleSort(A, n);
	printf("ð����������");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
	return 0;
}