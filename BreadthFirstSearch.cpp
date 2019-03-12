#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <queue>
using namespace std;

enum Color{
	WHITE,	// 新节点
	GRAY,	// 发现节点，加队列待处理
	BLACK,	// 弹出队列，处理完毕
};

template<typename T>
struct ListNode
{
	ListNode(const T t, ListNode *node) : val(t), next(node){};
	T val;
	list<ListNode*> *next;
};

template<typename T>
struct TreeNode
{
	TreeNode() {};
	TreeNode(const T &t) : val(t){
		dist = 0;
		father = NULL;
		color = WHITE;
	}
	T val;
	int dist;	// 高度
	TreeNode *father;
	Color color;	// 标记只是用来辅助，可以删除不用
};

void BFS(map<char, list<char> > &gra, const char root, map<char, TreeNode<char> > &tree)
{
	int size = gra.size();
	queue<TreeNode<char>*> que;
	for (map<char, list<char> >::iterator it = gra.begin(); it != gra.end(); ++it)
	{
		tree[it->first] = TreeNode<char>(it->first);
	}
	tree[root].color = GRAY;
	que.push(&tree[root]);		// 根节点加入处理队列

	while(!que.empty())
	{
		TreeNode<char>* pNode = que.front();
		que.pop();
		// 从根节点开始把所有遇到的节点加入处理队列，按队列次序处理，每个节点加标记，不重复处理
		for(list<char>::iterator it = gra[pNode->val].begin(); it != gra[pNode->val].end(); ++it)
		{
			if (tree[*it].color == WHITE)
			{
				tree[*it].color = GRAY;
				tree[*it].dist = pNode->dist + 1;
				tree[*it].father = pNode;
				que.push(&tree[*it]);
			}
		}
		pNode->color = BLACK;
	}
}

void PrintPath(map<char, TreeNode<char> > &tree, char root, char v)
{
	if (root == v)
		cout << root << endl;
	else if (tree[v].father == NULL)
		cout << "no path" << endl;
	else
	{
		PrintPath(tree, root, tree[v].father->val);
		cout << v << endl;
	}
}

int main10()
{
	//enum ccc{WHITE, GRAY, BLACK};

	map<char, list<char> > gra;
	list<char> list1;	// 邻接链表
	list1.push_back('s');
	list1.push_back('v');
	gra['r'] = list1;
	list<char> list2;	// 邻接链表
	list2.push_back('r');
	list2.push_back('w');
	gra['s'] = list2;
	list<char> list3;	// 邻接链表
	list3.push_back('u');
	list3.push_back('w');
	list3.push_back('x');
	gra['t'] = list3;
	list<char> list4;	// 邻接链表
	list4.push_back('t');
	list4.push_back('x');
	list4.push_back('y');
	gra['u'] = list4;
	list<char> list5;	// 邻接链表
	list5.push_back('r');
	gra['v'] = list5;
	list<char> list6;	// 邻接链表
	list6.push_back('s');
	list6.push_back('t');
	list6.push_back('x');
	gra['w'] = list6;
	list<char> list7;	// 邻接链表
	list7.push_back('t');
	list7.push_back('u');
	list7.push_back('w');
	list7.push_back('y');
	gra['x'] = list7;
	list<char> list8;	// 邻接链表
	list8.push_back('u');
	list8.push_back('x');
	gra['y'] = list8;

	map<char, TreeNode<char> > tree;
	BFS(gra, 's', tree);
	PrintPath(tree, 's', 'x');

	getchar();
	return 0;
}