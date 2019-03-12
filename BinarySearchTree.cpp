// ����������
#include "stdafx.h"
#include <iostream>
using namespace std;

template<typename T>
struct TreeNode
{
	T key;
	TreeNode<T> *p;
	TreeNode<T> *left;
	TreeNode<T> *right;
};

// �������
template<typename T>
void InorderTreeWalk(TreeNode<T> *x)
{
	if (!x)
		return;
	InorderTreeWalk(x->left);
	cout << x->key << " ";
	InorderTreeWalk(x->right);
}

template<typename T>
TreeNode<T>* TreeSearch(TreeNode<T> *x, T k)
{
	if (!x || k == x->key)
		return x;
	if (k < x->key)
		return TreeSearch(x->left, k);
	else
		return TreeSearch(x->right, k);
}

template<typename T>
TreeNode<T>* TreeMinimum(TreeNode<T> *x)
{
	if (!x)
		return x;
	while (x->left)
		x = x->left;
	return x;
}

template<typename T>
TreeNode<T>* TreeMaximum(TreeNode<T> *x)
{
	if (!x)
		return x;
	while (x->right)
		x = x->right;
	return x;
}

// ���
template<typename T>
TreeNode<T>* TreeSuccessor(TreeNode<T> *x)
{
	// �������������һ�����x���ҽ�㣬ֱ�����ҽ�����Сֵ���Ǻ��
	if (x->right)
		return TreeMinimum(x->right);
	// �ڶ���������������һ�����ȣ�������ȵ�������x��x������
	TreeNode<T>* y = x->p;
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
TreeNode<T>* TreePredecessor(TreeNode<T> *x)
{
	if (x->left)
		return TreeMaximum(x->left);
	TreeNode<T> *y = x->p;
	while (y != nullptr && x == y->left)
	{
		x = y;
		y = y->p;
	}
	return y;
}

template<typename T>
TreeNode<T>* TreeInsert(TreeNode<T> *x, T k)
{
	TreeNode<T> *y = nullptr;
	while (x)
	{
		y = x;
		if (k < x->key)
			x = x->left;
		else
			x = x->right;
	}
	TreeNode<T> *newnode = new TreeNode<T>();
	memset(newnode, 0, sizeof(TreeNode<T>));
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
void Transplant(TreeNode<T> *root, TreeNode<T> *dest, TreeNode<T> *src)
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
void TreeDelete(TreeNode<T> *root, TreeNode<T> *z)
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
		TreeNode<T> *y = TreeMinimum(z->right);	
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

int mainbs()
{
	TreeNode<int> node1;
	node1.key = 6;
	node1.p = nullptr;
	TreeNode<int> node2;
	node2.key = 5;
	node2.p = &node1;
	node1.left = &node2;
	TreeNode<int> node3;
	node3.key = 2;
	node3.p = &node2;
	node3.left = nullptr;
	node3.right = nullptr;
	node2.left = &node3;
	TreeNode<int> node4;
	node4.key = 5;
	node4.p = &node2;
	node4.left = nullptr;
	node4.right = nullptr;
	node2.right = &node4;
	TreeNode<int> node5;
	node5.key = 7;
	node5.p = &node1;
	node5.left = nullptr;
	node1.right = &node5;
	TreeNode<int> node6;
	node6.key = 8;
	node6.p = &node5;
	node6.left = nullptr;
	node6.right = nullptr;
	node5.right = &node6;


	//InorderTreeWalk(&node1);
	TreeNode<int> *p = TreeSearch(&node1, 5);
	if (p)
		cout << p->key << endl;
	p = TreeMinimum(&node1);
	if (p)
		cout << "minimum:" << p->key << endl;
	p = TreeMaximum(&node1);
	if (p)
		cout << "maximum:" << p->key << endl;
	p = TreeSuccessor(&node4);
	if (p)
		cout << "successor:" << p->key << endl;
	p = TreePredecessor(&node4);
	if (p)
		cout << "Predecessor:" << p->key << endl;
	TreeNode<int> *newnode = TreeInsert(&node1, 10);
	cout << newnode->p->key << endl;


	InorderTreeWalk(&node1);
	cout << endl;
	TreeDelete(&node1, &node2);
	InorderTreeWalk(&node1);
	//TreeDelete(&node1, &node1);
	//InorderTreeWalk(&node5);

	//getchar();
	return 0;
}