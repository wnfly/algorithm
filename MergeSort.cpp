#include "stdafx.h"
#include <iostream>
using namespace std;

void Merge(int *A, const int start, const int med, const int end)
{
	int n1 = med - start + 1;
	int n2 = end - med; 
	int *L = new int[n1 + 1];	// +1最后个是哨兵
	int *R = new int[n2 + 1];
	for	(int i = 0, j = start - 1; i < n1; ++i, ++j)
	{
		L[i] = A[j];
	}
	for (int i = 0, j = med; i < n2; ++i, ++j)
	{
		R[i] = A[j];
	}
	L[n1] = INT_MAX;	// 哨兵
	R[n2] = INT_MAX;
	int i = 0;
	int j = 0;
	//cout << i << ',' << j << endl; // 此处的i和j在vs2010的监视时显示错误的值，但打印和使用时是对的
	for (int k = start - 1; k < end; ++k)
	{
		// 在一边的L或R比较完了之后 ，再比较会数组越界，这时使用哨兵来比较的话代码比较容易写
		if (L[i] <= R[j])	
			A[k] = L[i++];
		else
			A[k] = R[j++];
	}
	delete [] L;
	delete [] R;
}

const int aaa = 11;
/* 归并排序
 * start从1开始，而非从索引0开始
 */
void MergeSort(int *A, const int start, const int end)
{
	if (start < end)
	{
		int med = (end + start) / 2;	// 从1开始这样算正确
		//cout << med << " ";
		MergeSort(A, start, med);
		MergeSort(A, med + 1, end);
		Merge(A, start, med, end);
	}
}

int mainms()
{
	int arr[] = {2,8,7,1,3,5,6,4};
	//int arr[] = {4,2,3,1};
	int length =  sizeof(arr) / sizeof(int);

	MergeSort(arr, 1, length);
	for (int i = 0; i < length; ++i)
	{
		cout << arr[i] << " ";
	}

	cout << endl << aaa << endl;

	//getchar();
	return 0;
}