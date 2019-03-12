#include "stdafx.h"
#include <iostream>
using namespace std;

// 把最尾部的项在数组中的位置确定好之后，再把前后安排好
template<typename T>
T partition(T *A, const int start, const int end)
{
	T x = A[end];
	int i = start - 1;  // i = -1也可以？
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

// start和end是索引第一和最后
template<typename T>
void quicksort(T *A, const int start, const int end)
{
	if (start < end)
	{
		int q = partition(A, start, end);// 先排序最后一个数字到最终位置
		quicksort(A, start, q - 1);// 再分别排序确定位置的数字的前后
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