//#define NDEBUG 
#include "stdafx.h"
#include <iostream>
#include <cassert>
using namespace std;

int myatoi(const char *str)
{
	assert(str);
	int n = 0;
	bool isMinus = false;
	if (*str == '-')
	{
		isMinus = true;
		++str;
	}
	//while(*str != '\0')
	while(*str >= '0' && *str <= '9') // (!isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		++str;
	}
	return isMinus ? -n : n;
}

int main8()
{
	int i = myatoi("-1234560");
	//myatoi(NULL);
	//atoi("2323");
	cout << i << endl;


	getchar();
	return 0;
}