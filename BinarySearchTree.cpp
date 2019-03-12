// 二叉搜索树
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

// 中序遍历
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

// 后继
template<typename T>
TreeNode<T>* TreeSuccessor(TreeNode<T> *x)
{
	// 分两种情况，第一次情况x有右结点，直接找右结点的最小值就是后继
	if (x->right)
		return TreeMinimum(x->right);
	// 第二种情况，找最近的一个祖先，这个祖先的左孩子是x或x的祖先
	TreeNode<T>* y = x->p;
	//while (y != nullptr && x == y->right)	// 书上这句
	while (!(y == nullptr || x == y->left))	// 这句是自己写的，更容易理解
	{// 向上一级去寻找后继
		x = y;
		y = y->p;
	}
	return y;
}

// 前驱
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
		// x是空树，新结点是根结点
	}
	else if (k < y->key)
		y->left = newnode;
	else
		y->right = newnode;
	return newnode;
}

// 移动子树，注意并没有处理src->left和right的更新，只是处理父结点和父结点中的子结点。
template<typename T>
void Transplant(TreeNode<T> *root, TreeNode<T> *dest, TreeNode<T> *src)
{
	if (!dest)
		return;
	//先把目标的父结点的子结点修改成src
	if (dest->p == nullptr)
		root = src;
	else if (dest->p->left == dest)
		dest->p->left = src;
	else
		dest->p->right = src;
	//再把src的父结点修改成目标的父结点，这样就相当于覆盖结点了
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
	else// 到这一步说明z的左右孩子是都有的
	{
		// 这句就是找z的右子树的最小值,找出来的值就是z的后继，
		// 而且y因为是右子树中的最小值，是没有左孩子的
		TreeNode<T> *y = TreeMinimum(z->right);	
		if (y->p != z)
		{// 如果z的后继不是右孩子的话，这是最复杂，步骤最多的一步，需要多一步将y的右孩子移到y的位置，再将y移动到z的位置
			Transplant(root, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		Transplant(root, z, y);// 如果y是z的右孩子，可以直接将y移动到z的位置
		y->left = z->left;	// 没有左孩子，所以可以直接用z的左孩子覆盖
		y->left->p = y;		// 把z的左孩子的父结点改为y
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