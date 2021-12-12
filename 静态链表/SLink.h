#pragma once
#include "SNode.h"
#include <iostream>
using namespace std;

const int MAXSIZE = 100;		//每次申请堆数组的大小
const int RANGE_ERROR = 1001;	//越界抛出1001

template <class ElemType> class SLink		//当前 单向 非循环  可以之后再改
{
protected:
	SNode<ElemType>* node;		//用node指向堆数组首结点 以此作为静态链表首结点 node[0]与普通链表的首结点类似
	int avail;					//静态链表下一个空位的下标 将除去node[0]外所有没有data的结点 都归为空表 空表的首结点为avail avail起到增删的重要作用
	int length;					//当前已拥有的结点数(不包括head)

public:
	SLink();					//分配空间 用next把结点连在一起 创造空表 
	virtual ~SLink();
	void Traverse(bool write = true) const;		//遍历(输出/不输出)
	void Insert(const ElemType& e);				//尾插法 //插入完成后 avail自动向后移，删除完成后 avail变到被删处的位置 
	void Insert(int loc, const ElemType& e);		//插入，使e成为链表第loc个元素(不算head)
	int Find(const ElemType& e);
	void Delete(int loc);
	void Reverse();				//链表倒置
        void Sort();

};


template<class ElemType> SLink<ElemType>::SLink() : length(0), avail(1)
{
	node = new SNode<ElemType>[MAXSIZE];
	for (int i = 0; i < MAXSIZE - 1; i++)
	{
		node[i].next = i + 1;		//第i个元素的next指向i+1 最后元素默认指-1
	}
}

template<class ElemType> SLink<ElemType>::~SLink()
{
	delete[] node;
	length = 0;
}

template <class ElemType> void SLink<ElemType>::Traverse(bool write) const	//write == 1 输出一遍链表, write == 0 仅移动到表尾
{
	int p = node[0].next;
	if (write)
	{
		//if (length > 0) 
			cout << "HEAD -> ";
		while (p != -1 && p != avail)
		{
			cout << node[p].data << " -> ";
			p = node[p].next;
		}
		cout << "NULL" << endl;
	}
	else
	{
		while (p != -1 && p != avail)
		{
			p = node[p].next;					//考虑来个return 改个返回类型
		}
	}
}

template<class ElemType> void SLink<ElemType>::Insert(const ElemType& e)
{
	node[avail].data = e;
	avail = node[avail].next;		//avail移动到空表的下一个位置
	length++;
}

template<class ElemType> void SLink<ElemType>::Insert(int loc, const ElemType& e)
{
	if (loc < 1 || loc > length + 1)
		throw RANGE_ERROR;
	node[avail].data = e;
	int j = 0;							//loc处的前一个结点
	int p = avail;					//记录这个刚有数据的结点
	avail = node[avail].next;		//avail移动到空表的下一个位置

	for (int i = 0; i < loc - 1; i++)		//找到j
	{
		j = node[j].next;
	}
	int d = j;
	while (node[d].next != p)
		d = node[d].next;
	node[d].next = avail;
	node[p].next = node[j].next;		//断链重连
	node[j].next = p;
	length++;
}

template<class ElemType>
int SLink<ElemType>::Find(const ElemType& e)
{
	int j = 0, k = 0;//j游标，k计数
	for (; node[j].next != avail; j = node[j].next,k++)
	{
		if (node[j].data == e) return k;
	}
	if (node[j].data == e) return k;
	return -1;
}

template<class ElemType> void SLink<ElemType>::Delete(int loc) 
{
	if (loc < 1 || loc > length + 1)
		throw RANGE_ERROR;
	int j = 0;								//loc处的前一个结点
	for (int i = 0; i < loc - 1; i++)		//找到j
	{
		j = node[j].next;
	}
	int k = node[j].next;					//记录loc处的结点
	node[j].next = node[k].next;
	int p = avail;							//记录原avail
	avail = k;								//被删的结点自动成为新的avail
	node[p].next = avail;					//avail间生成联系
	while (node[j].next != p)				//让j到有数据表的表尾
		j = node[j].next;
	node[j].next = avail;					
	length--;
}

template<class ElemType> void SLink<ElemType>::Reverse()
{
	if (length == 1)
		return;
	int p = 0;
	int q = node[0].next;
	int r = node[q].next;		//p -> q -> r
	node[q].next = avail;		//avail只改一次
	while (r != avail)
	{
		p = q;
		q = r;
		r = node[r].next;

		node[q].next = p;
	}
	node[0].next = q;
}

template<class ElemType>
void SLink<ElemType>::Sort()
{
	if (length == 1) return;
	int p = node[0].next;
	for (int q = p; q != avail; q = p)
	{
		for (int r = q; r != avail; r = node[r].next)
		{
			if (node[q].data > node[r].data)
				q = r;
		}
		ElemType Temp = node[p].data;
		node[p].data = node[q].data;
		node[q].data = Temp;
		p = node[p].next;
	}
}


















/*
template <class ElemType>
class SLink		//当前带头结点 单向 非循环  可以之后再改
{
protected:
	SNode<ElemType> head;		//带头结点	p = link[p.next]相当于p = p->next
	int avail;			//静态链表空位的下标
	int length;			//当前已拥有的结点数(不包括head)
	int max_length;		//最多能拥有的结点数(包括了head)(由初始所申请的动态内存决定)

public:
	//基本辅助函数: 判空,清空,返回长度/最大长度,遍历 等

	//基本功能函数：增,删,改,查,倒置,合并,排序 等
	void SLink<ElemType>::Insert(const ElemType& e);		//尾插

	//考虑为Max_length扩容(重新分配更大的内存空间 → copy → delete)  或者 考虑让两个不同的静态链表建立联系来扩容

	//运算符 + 输入输出流重载

	//四大函数
	SLink();
	SLink(ElemType arr[], int n);
	virtual ~SLink();
	SLink(const SLink<ElemType>& link);
	SLink<ElemType>& operator = (const SLink<ElemType>& link);

};

template <class ElemType> SLink<ElemType>::SLink()
{
	head = new SNode<ElemType>;		//构造空头
	avail = -1;					//链表没有空位
	length = 0;
}

template <class ElemType> void SLink<ElemType>::Insert(const ElemType& e)
{
	SNode<ElemType> p, q;
	q = new Node<ElemType>(e, -1);    // 生成新结点q
	for (p = head; p.next != -1; p = p->next);	// p指向表尾结点
	p->next = q;                        // 在单链表的表尾位置插入新结点
	length++;							// 插入成功后，单链表长度加1

}




template <class ElemType> SLink<ElemType>::SLink(ElemType arr[], int n)
{
	max_length = 2 * n + 1;
	ElemType link = new SNode<ElemType>(max_length);		//申请有两倍堆空间的sll数组

	link[0] = head;								//按照 0->n 顺序设定next为自然数集 与插入不同
	for (int i = 0; i < n; i++)
	{
		link[i].next = i + 1;
		link[link[i].next].data = arr[i];
	}
	length = n;
}

template <class ElemType> SLink<ElemType>::~SLink()
{
	//Clear();
	delete[]head;
}


template <class ElemType> SLink<ElemType>::SLink(const SLink<ElemType>& link2)
{
	max_length = link2.max_length;
	ElemType link = new SNode<ElemType>(max_length);
	ElemType p = link[0] = head;
	ElemType p2 = link2.head;
	p.next = p2.next;

	for (int i = 0; i < link2.length; i++)
	{
		//p = link2[p.next];
		link[p.next].data = link2[p2.next].data;
		link[p.next].next = link2[p2.next].next;
		p = link[p.next];
		p2 = link2[p2.next];
	}
	length = n;
}*/
