#include "stdafx.h"
#include <iostream>
using namespace std;

template <typename T>
struct ListNode
{
	T val;
	ListNode* next;
};

template <typename T>
ListNode<T>* FindMiddleNode(ListNode<T> *root)
{
	ListNode<T> *l1 = root, *l2 = root;
	int len = 1;
	while(l2)
	{
		l2 = l2->next;
		++len;
		if (len % 2 == 1)
			l1 = l1->next;
	}
	return l1;
}

int mainmi()
{
	ListNode<int> l5;
	l5.val = 5;
	l5.next = NULL;
	ListNode<int> l4;
	l4.val = 4;
	l4.next = &l5;
	ListNode<int> l3;
	l3.val = 3;
	l3.next = &l4;
	ListNode<int> l2;
	l2.val = 2;
	l2.next = &l3;
	ListNode<int> l1;
	l1.val = 1;
	l1.next = &l2;

	ListNode<int>  *mid = FindMiddleNode(&l1);
	if (mid)
		cout << mid->val << endl;

	return 0;
}