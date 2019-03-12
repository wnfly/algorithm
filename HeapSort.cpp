#include "stdafx.h"
#include <iostream>
using namespace std;

inline int Parent(int i)
{
	return i / 2;
}

inline int Left(int i)
{
	return i * 2;
}

inline int Right(int i)
{
	return i * 2 + 1;
}

void MaxHeapify(int *A, int size, int i)
{
	int l = Left(i);
	int r = Right(i);
	int largest = 0;
	if (l <= size && A[l - 1] > A[i - 1])
		largest = l;
	else
		largest = i;
	if (r <= size && A[r - 1] > A[largest - 1])
		largest = r;
	if (largest != i)
	{
		swap(A[largest - 1], A[i - 1]);
		MaxHeapify(A, size, largest);
	}
}

void BuildMaxHeap(int *A, int size)
{
	for (int i = size / 2; i >= 1; --i)
	{
		MaxHeapify(A, size, i);
	}
}

void HeapSort(int *A, int size)
{
	BuildMaxHeap(A, size);
	for (int i = size; i > 1; --i)
	{
		swap(A[0], A[i - 1]);
		--size;
		MaxHeapify(A, size, 1);
	}
}

int mainhaep()
{
	int arr[] = {16,4,10,14,7,9,3,2,8,1,20};
	int size = sizeof(arr) / sizeof(int);
	int *a = arr;
	cout << sizeof(arr) << endl;
	cout << sizeof(a) << endl;
	cout << sizeof(*a) << endl;
	MaxHeapify(arr, size, 2);

	BuildMaxHeap(arr, size);
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
	HeapSort(arr, size);
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}