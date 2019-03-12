#include "stdafx.h"
#include <iostream>
#include <cassert>
#include <string>
#include <cmath>
using namespace std;

string dec2bin(const int n)
{
	int i = n;
	string binary;
	while(i != 0)
	{
		if (0 == i % 2)
			binary.insert(binary.begin(), '0');
		else
			binary.insert(binary.begin(), '1');
		i /= 2;
	}
	return binary;
}

int bin2dec(const char* str, const int len)
{
	assert(str);
	int n = 0;
	for (int i = len - 1, j = 0; i >= 0; --i, ++j)
	{
		if (str[j] != '0' && str[j] != '1')
			break;
		if (str[j] == '1')
			n += pow(2.0, i);	// ÃÝ
	}
	return n;
}

int main9()
{

	int i = 1 << 4;
	cout << i << endl;
	string str = dec2bin(1 << 4);
	cout << str << endl;

	cout << bin2dec("10000", 5) << endl;

	//int hex = 382;  // ¿ÉÒÔµÄ
	//cout << hex << 100 << endl;


	getchar();
	return 0;
}