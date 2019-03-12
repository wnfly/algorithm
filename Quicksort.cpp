#include "stdafx.h"
#include <iostream>
using namespace std;

// ����β�������������е�λ��ȷ����֮���ٰ�ǰ���ź�
template<typename T>
T partition(T *A, const int start, const int end)
{
	T x = A[end];
	int i = start - 1;  // i = -1Ҳ���ԣ�
	for(int j = start; j < end; ++j)
	{
		if (A[j] <= x)
		{
			++i;
			swap(A[j], A[i]);
		}
	}

	++i;
	swap(A[end], A[i]);
	return i;
}

// start��end��������һ�����
template<typename T>
void quicksort(T *A, const int start, const int end)
{
	if (start < end)
	{
		int q = partition(A, start, end);// ���������һ�����ֵ�����λ��
		quicksort(A, start, q - 1);// �ٷֱ�����ȷ��λ�õ����ֵ�ǰ��
		quicksort(A, q + 1, end);
	}
}

int main6()
{
	int arr[] = {2,8,7,1,3,5,6,4};
	int length =  sizeof(arr) / sizeof(int);

	quicksort(arr, 0, length - 1);
	for (int i = 0; i < length; ++i)
	{
		cout << arr[i] << " ";
	}

	getchar();
	return 0;
}