#include "stdafx.h"
#include <iostream>
#include <list>
using namespace std;

// 简单一般用此结构
template<typename T>
struct ST_LIST_NODE{
	ST_LIST_NODE(){
		pnext = nullptr;
	}
	ST_LIST_NODE(T t, ST_LIST_NODE *p){
		val = t;
		pnext = p;
	}
	T val;
	ST_LIST_NODE *pnext;
};

// 自己优化的方法使用模板类
template<typename T>
class List
{
private:
	T t;
	List<T>* pnext;
public:
	List(T t, List<T>* pnext = nullptr)
	{
		this->t = t;
		this->pnext = pnext;
	}
	List<T>* next(){
		return pnext;
	}
	void setNext(List<T>* next){
		this->pnext = next;
	}
	T value(){
		return t;
	}
	bool hasNext(){
		return !pnext ? false : true;
	}
};

// 非递归方法，还有递归方法
template<typename T>
List<T>* reverseList(List<T> *head)
{
	if (!head)
		return nullptr;
	if (!head->hasNext())
		return head;

	List<T>* pPrev = nullptr, *pNext = nullptr;
	// ------------- 反转主要是这个循环的代码---------------
	while(head)
	{
		pNext = head->next();
		head->setNext(pPrev);
		pPrev = head;
		head = pNext;
	}

	return pPrev;	// 注意head已经为空了，这时pPrev是头部的指针
};

template<typename T>
void DisplayList(List<T> *li)
{
	if (!li)
		return;
	while(1) 
	{
		cout << li->value() << " ";
		if (!li->hasNext())
			break;
		li = li->next();
	}
	cout << endl;
}

int mainllW()
{
	List<int> li4(4);
	List<int> li3(3, &li4);
	List<int> li2(2, &li3);
	List<int> li1(1, &li2);

	DisplayList(&li1);

	//cout << li1.value() << endl;
	//cout << li1.next()->value() << endl;
	//cout << li1.next()->next()->value() << endl;
	//cout << li1.next()->next()->next()->value() << endl;

	List<int> *rli = reverseList(&li1);
	DisplayList(rli);

	ST_LIST_NODE<int> list2(99, nullptr);
	list2.val = 999;
	cout << list2.val << endl;

	getchar();
	return 0;
}
