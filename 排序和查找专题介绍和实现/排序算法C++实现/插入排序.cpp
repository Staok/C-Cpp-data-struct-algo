#include<iostream>
using namespace std;
void InsertionSort(int A[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int get = A[i];
		int j = i - 1;
		while (j >= 0 && A[j] > get)
		{
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = get;
	}
}
int main03()
{

	int A[] = { 6, 5, 3, 1, 8, 7, 2, 4 };// ��С�����������
	int n = sizeof(A) / sizeof(int);
	InsertionSort(A, n);
	printf("������������");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
	system("pause");

	return 0;
}