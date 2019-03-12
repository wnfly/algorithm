#include "stdafx.h"
#include <iostream>
#include <climits>
#include <limits>
using namespace std;


struct SetFound
{
	int low;
	int high;
	long long sum;
	//int sum;
};

// �ǵݹ顢����ʱ���������������㷨
// ����һ�������е�ʹ�÷��β��Եĵݹ��㷨��Ч��û�������
SetFound FindMaxSubarray(int *A, const int length) 
{
	SetFound maxsub = {0};
	maxsub.sum = A[0];
	for (int i = 1; i < length; ++i)
	{
		//int maxTailSum = A[i];
		long long maxTailSum = A[i];
		int maxHeadFromTail = i;
		//int sumFromTail = A[i];
		long long sumFromTail = A[i];
		for (int j = i - 1; j >= 0; --j)
		{
			sumFromTail += (long long)A[j];	// ʹ��long long���Է�ֹint������ر��ǲ������ͣ���������ʱ
			//sumFromTail *= A[j];
			if (sumFromTail > maxTailSum)
			{
				maxHeadFromTail = j;
				maxTailSum = sumFromTail;
			}
		}
		
		if (maxsub.sum < maxTailSum)
		{
			maxsub.low = maxHeadFromTail;
			maxsub.high = i;
			maxsub.sum = maxTailSum;
		}
	}

	return maxsub;
}

int main2()
{
	int arr[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

	cout << sizeof(arr) << endl;
	SetFound maxsub = FindMaxSubarray(arr, sizeof(arr) / sizeof(int));
	cout << arr[maxsub.low] << "~" << arr[maxsub.high] << endl;
	cout << maxsub.low + 1 << "~" << maxsub.high + 1 << " sum:" << maxsub.sum << endl;

	getchar();
	return 0;
}