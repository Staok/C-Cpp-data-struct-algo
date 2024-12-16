#include<iostream>
using namespace std;

void quicksort(int a[],int left, int right) {
	int i, j, t, temp;
	if (left > right)
		return;
	temp = a[left]; //temp�д�ľ��ǻ�׼��
	i = left;
	j = right;
	while (i != j) { //˳�����Ҫ��Ҫ�ȴ��ұ߿�ʼ��
		while (a[j] >= temp && i < j)
			j--;
		while (a[i] <= temp && i < j)//�����ұߵ�
			i++;
		if (i < j)//�����������������е�λ��
		{
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
	}
	//���ս���׼����λ
	a[left] = a[i];
	a[i] = temp;
	quicksort(a,left, i - 1);//����������ߵģ�������һ���ݹ�Ĺ���
	quicksort(a,i + 1, right);//���������ұߵ� ��������һ���ݹ�Ĺ���
}
int main() {
	int i;
	int array[] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
	int n = sizeof(array) / sizeof(int);
	quicksort(array,0, n-1); //�����������
	//��������Ľ��
	for (i = 0; i < n; i++)
		printf("%d ", array[i]);
	return 0;
}
