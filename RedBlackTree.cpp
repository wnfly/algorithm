// �����
#include "stdafx.h"
#include <iostream>
using namespace std;

enum RDTreeColor { BLACK, RED };

template<typename T>
struct RDTreeNode
{
	RDTreeColor color;
	T key;
	RDTreeNode<T> *p;
	RDTreeNode<T> *left;
	RDTreeNode<T> *right;
};

// �������
template<typename T>
void InorderTreeWalk(RDTreeNode<T> *x)
{
	if (!x)
		return;
	InorderTreeWalk(x->left);
	cout << x->key << " ";
	InorderTreeWalk(x->right);
}

template<typename T>
RDTreeNode<T>* TreeSearch(RDTreeNode<T> *x, T k)
{
	if (!x || k == x->key)
		return x;
	if (k < x->key)
		return TreeSearch(x->left, k);
	else
		return TreeSearch(x->right, k);
}

template<typename T>
RDTreeNode<T>* TreeMinimum(RDTreeNode<T> *x)
{
	if (!x)
		return x;
	while (x->left)
		x = x->left;
	return x;
}

template<typename T>
RDTreeNode<T>* TreeMaximum(RDTreeNode<T> *x)
{
	if (!x)
		return x;
	while (x->right)
		x = x->right;
	return x;
}

// ���
template<typename T>
RDTreeNode<T>* TreeSuccessor(RDTreeNode<T> *x)
{
	// �������������һ�����x���ҽ�㣬ֱ�����ҽ�����Сֵ���Ǻ��
	if (x->right)
		return TreeMinimum(x->right);
	// �ڶ���������������һ�����ȣ�������ȵ�������x��x������
	RDTreeNode<T>* y = x->p;
	//while (y != nullptr && x == y->right)	// �������
	while (!(y == nullptr || x == y->left))	// ������Լ�д�ģ����������
	{// ����һ��ȥѰ�Һ��
		x = y;
		y = y->p;
	}
	return y;
}

// ǰ��
template<typename T>
RDTreeNode<T>* TreePredecessor(RDTreeNode<T> *x)
{
	if (x->left)
		return TreeMaximum(x->left);
	RDTreeNode<T> *y = x->p;
	while (y != nullptr && x == y->left)
	{
		x = y;
		y = y->p;
	}
	return y;
}

template<typename T>
RDTreeNode<T>* TreeInsert(RDTreeNode<T> *x, T k)
{
	RDTreeNode<T> *y = nullptr;
	while (x)
	{
		y = x;
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}
	RDTreeNode<T> *newnode = new RDTreeNode<T>();
	memset(newnode, 0, sizeof(RDTreeNode<T>));
	newnode->key = k;
	newnode->p = y;
	if (!y) {
		// x�ǿ������½���Ǹ����
	}
	else if (k < y->key)
		y->left = newnode;
	else
		y->right = newnode;
	return newnode;
}

// �ƶ�������ע�Ⲣû�д���src->left��right�ĸ��£�ֻ�Ǵ������͸�����е��ӽ�㡣
template<typename T>
void Transplant(RDTreeNode<T> *root, RDTreeNode<T> *dest, RDTreeNode<T> *src)
{
	if (!dest)
		return;
	//�Ȱ�Ŀ��ĸ������ӽ���޸ĳ�src
	if (dest->p == nullptr)
		root = src;
	else if (dest->p->left == dest)
		dest->p->left = src;
	else
		dest->p->right = src;
	//�ٰ�src�ĸ�����޸ĳ�Ŀ��ĸ���㣬�������൱�ڸ��ǽ����
	if (src)
		src->p = dest->p;
}

template<typename T>
void TreeDelete(RDTreeNode<T> *root, RDTreeNode<T> *z)
{
	if (!root || !z)
		return;
	if (z->left == nullptr)
		Transplant(root, z, z->right);
	else if (z->right == nullptr)
		Transplant(root, z, z->left);
	else// ����һ��˵��z�����Һ����Ƕ��е�
	{
		// ��������z������������Сֵ,�ҳ�����ֵ����z�ĺ�̣�
		// ����y��Ϊ���������е���Сֵ����û�����ӵ�
		RDTreeNode<T> *y = TreeMinimum(z->right);
		if (y->p != z)
		{// ���z�ĺ�̲����Һ��ӵĻ���������ӣ���������һ������Ҫ��һ����y���Һ����Ƶ�y��λ�ã��ٽ�y�ƶ���z��λ��
			Transplant(root, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		Transplant(root, z, y);// ���y��z���Һ��ӣ�����ֱ�ӽ�y�ƶ���z��λ��
		y->left = z->left;	// û�����ӣ����Կ���ֱ����z�����Ӹ���
		y->left->p = y;		// ��z�����ӵĸ�����Ϊy
	}
	//delete z;
}

// ��������ת֮ǰ�Ĵ����������ģ�
// a(x.left) < x < b(y.left or x.right) < y < c(y.right)
template<typename T>
void LeftRotate(RDTreeNode<T> **root, RDTreeNode<T> *x)
{
	if (!x->right)
		return;
	RDTreeNode<T> *y = x->right;
	// �Ȱ�y���������ŵ�x��������
	x->right = y->left;
	if (x->right)
		x->right->p = x;
	// �ٰ�x�ĸ������ӽ��ָ��y
	y->p = x->p;
	if (x->p == nullptr)
		*root = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	// ����x�ŵ�y������
	x->p = y;
	y->left = x;
}

// ������
template<typename T>
void RightRotate(RDTreeNode<T> **root, RDTreeNode<T> *y)
{
	if (!y->left)
		return;
	RDTreeNode<T> *x = y->left;
	// �Ȱ�x���������ŵ�y��������
	y->left = x->right;
	if (y->left)
		y->left->p = y;
	// �ٰ�x�ĸ������ӽ��ָ��y
	x->p = y->p;
	if (y->p == nullptr)
		*root = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	// ����y�ŵ�x���Һ���
	y->p = x;
	x->right = y;
	
}

int mainrb()
{
	RDTreeNode<int> node1;
	node1.key = 6;
	node1.p = nullptr;
	RDTreeNode<int> node2;
	node2.key = 5;
	node2.p = &node1;
	node1.left = &node2;
	RDTreeNode<int> node3;
	node3.key = 2;
	node3.p = &node2;
	node3.left = nullptr;
	node3.right = nullptr;
	node2.left = &node3;
	RDTreeNode<int> node4;
	node4.key = 5;
	node4.p = &node2;
	node4.left = nullptr;
	node4.right = nullptr;
	node2.right = &node4;
	RDTreeNode<int> node5;
	node5.key = 7;
	node5.p = &node1;
	node5.left = nullptr;
	node1.right = &node5;
	RDTreeNode<int> node6;
	node6.key = 8;
	node6.p = &node5;
	node6.left = nullptr;
	node6.right = nullptr;
	node5.right = &node6;


	//InorderTreeWalk(&node1);
	//RDTreeNode<int> *newnode = TreeInsert(&node1, 10);
	//cout << newnode->p->key << endl;

	InorderTreeWalk(&node1);
	cout << endl;
	TreeDelete(&node1, &node2);
	InorderTreeWalk(&node1);
	//TreeDelete(&node1, &node1);
	//InorderTreeWalk(&node5);



	//getchar();
	return 0;
}