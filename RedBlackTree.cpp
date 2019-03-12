// 红黑树
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

// 中序遍历
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

// 后继
template<typename T>
RDTreeNode<T>* TreeSuccessor(RDTreeNode<T> *x)
{
	// 分两种情况，第一次情况x有右结点，直接找右结点的最小值就是后继
	if (x->right)
		return TreeMinimum(x->right);
	// 第二种情况，找最近的一个祖先，这个祖先的左孩子是x或x的祖先
	RDTreeNode<T>* y = x->p;
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
void Transplant(RDTreeNode<T> *root, RDTreeNode<T> *dest, RDTreeNode<T> *src)
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
void TreeDelete(RDTreeNode<T> *root, RDTreeNode<T> *z)
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
		RDTreeNode<T> *y = TreeMinimum(z->right);
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

// 左旋。旋转之前的次序是这样的：
// a(x.left) < x < b(y.left or x.right) < y < c(y.right)
template<typename T>
void LeftRotate(RDTreeNode<T> **root, RDTreeNode<T> *x)
{
	if (!x->right)
		return;
	RDTreeNode<T> *y = x->right;
	// 先把y的左子树放到x的右子树
	x->right = y->left;
	if (x->right)
		x->right->p = x;
	// 再把x的父结点的子结点指向y
	y->p = x->p;
	if (x->p == nullptr)
		*root = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	// 最后把x放到y的左孩子
	x->p = y;
	y->left = x;
}

// 右旋。
template<typename T>
void RightRotate(RDTreeNode<T> **root, RDTreeNode<T> *y)
{
	if (!y->left)
		return;
	RDTreeNode<T> *x = y->left;
	// 先把x的右子树放到y的左子树
	y->left = x->right;
	if (y->left)
		y->left->p = y;
	// 再把x的父结点的子结点指向y
	x->p = y->p;
	if (y->p == nullptr)
		*root = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	// 最后把y放到x的右孩子
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