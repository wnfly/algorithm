#include "stdafx.h"
#include <iostream>
using namespace std;

// �ǵݹ�ⷨ
int factorialNorm(const int num)
{
	int f = 1;
	for (int i = 1; i <= num; ++i)
	{
		f *= i;
	}
	return f;
}

// �ݹ�ⷨ
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