#include "stdafx.h"
#include <iostream>
using namespace std;

// 非递归解法
int factorialNorm(const int num)
{
	int f = 1;
	for (int i = 1; i <= num; ++i)
	{
		f *= i;
	}
	return f;
}

// 递归解法
int factorial(const int num)
{
	if (num == 1 || num == 0)
		return 1;
	return num * factorial(num - 1);
}

int main3()
{
	cout << factorial(0) << endl;
	cout << factorialNorm(0) << endl;

	getchar();
	return 0;
}