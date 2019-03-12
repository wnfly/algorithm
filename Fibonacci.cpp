#include "stdafx.h"
#include <iostream>
using namespace std;

int Fibonacci(int num)
{
	if (num <= 0)
		return 0;
	if (num == 1)
		return 1;
	return Fibonacci(num - 1) + Fibonacci(num - 2);
}

int mainff()
{
	cout << Fibonacci(-1) << endl;
	cout << Fibonacci(3) << endl;
	cout << Fibonacci(5) << endl;
	cout << Fibonacci(11) << endl;
	cout << Fibonacci(12) << endl;

	getchar();
	return 0;
}