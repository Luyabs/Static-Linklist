#pragma once
#include "SNode.h"
#include <iostream>
#include <fstream>
using namespace std;

const int MAXSIZE = 7;			//每次申请堆数组的大小
const int RANGE_ERROR = 1001;		//越界抛出1001
const int OVER_FLOW = 1002;	       //length > maxlength时 抛出1002
const int NOT_FOUND = 1003;

template <class ElemType> class SLink		//当前 单向 非循环  可以之后再改
{
protected:
	SNode<ElemType>* node;		//用node指向堆数组首结点 以此作为静态链表首结点 node[0]与普通链表的首结点类似
	int avail;					//静态链表下一个空位的下标 将除去node[0]外所有没有data的结点 都归为空表 空表的首结点为avail avail起到增删的重要作用
	int length;					//当前已拥有的结点数(不包括head)
	int maxsize;

public:
	SLink();					//分配空间 用next把结点连在一起 创造空表 
	SLink(const SLink& link);
	SLink(const ElemType* E, const int& size);
	virtual ~SLink();
	void Traverse(bool mode = 1, ostream& out = cout) const;		//mode == 1 用->格式直观地输出链表, mode == 0 用方便文件读取的格式输出
	void Insert(const ElemType& e);				//尾插法 //插入完成后 avail自动向后移，删除完成后 avail变到被删处的位置 
	void Insert(int loc, const ElemType& e);		//插入，使e成为链表第loc个元素(不算head)
	void Set(int loc, const ElemType& e);
	int Find(const ElemType& e)const;
	ElemType Search(const int loc)const;
	int Length()const;
	ElemType Delete(int loc);
	void Reset();				//恢复初始状态
	void Reverse();				//链表倒置
	void Sort();
	void Enlarge(const int L);
	SLink<ElemType>& operator = (const SLink<ElemType>& S);

	void Save(const char* filename)const;	//文件输出
	void Load(const char* filename);	//文件读取

	template<class ElemType> friend istream& operator >>(istream& in, SLink<ElemType>& link);
};

template<class ElemType> ostream& operator <<(ostream& out, const SLink<ElemType>& link);


template<class ElemType> SLink<ElemType>::SLink() : length(0), avail(1), maxsize(MAXSIZE)
{
	node = new SNode<ElemType>[maxsize];
	for (int i = 0; i < maxsize - 1; i++)
	{
		node[i].next = i + 1;		//第i个元素的next指向i+1 最后元素默认指-1
	}
}

template<class ElemType> SLink<ElemType>::SLink(const SLink& link)
{
	node = new SNode<ElemType>[link.maxsize];
	for (int i = 0; i < link.maxsize; i++)
	{
		node[i] = link.node[i];
	}
	avail = link.avail;
	length = link.length;
	maxsize = link.maxsize;
}

template<class ElemType>
SLink<ElemType>::SLink(const ElemType* E, const int& size) :maxsize(MAXSIZE), length(size)
{
	while (length >= maxsize) 
	{
		maxsize = length *2;
		cout << endl << "扩容成功" << endl;
	}
	node = new SNode<ElemType>[maxsize];
	node[0].next = 1;
	for (int i = 0; i < length; i++)
	{
		node[i + 1].data = E[i];
		node[i + 1].next = i + 2;
	}
	avail = length + 1;
	for (int i = avail; i < maxsize - 1; i++)
	{
		node[i].next = i + 1;		//第i个元素的next指向i+1 最后元素默认指-1
	}
}


template<class ElemType> SLink<ElemType>::~SLink()
{
	delete[] node;
	length = 0;
}

template <class ElemType> void SLink<ElemType>::Traverse(bool mode, ostream& out) const	//mode == 1 用->格式直观地输出链表, mode == 0 用方便文件读取的格式输出链表
{
	int p = node[0].next;
	if (mode)
	{
		//if (length > 0) 
		out << "HEAD -> ";
		while (p != -1 && p != avail)
		{
			out << node[p].data << " -> ";
			p = node[p].next;
		}
		out << "NULL" << endl;
	}
	else
	{
		out << length + 1 << '\t';
		while (p != -1 && p != avail)
		{
			out << node[p].data << '\t';
			p = node[p].next;
		}
		out << endl;
	}
}

template<class ElemType> void SLink<ElemType>::Insert(const ElemType& e)
{
	if (length >= maxsize-1) throw OVER_FLOW;
	node[avail].data = e;
	avail = node[avail].next;		//avail移动到空表的下一个位置
	length++;
}

template<class ElemType> void SLink<ElemType>::Insert(int loc, const ElemType& e)
{
	if (length >= maxsize-1) throw OVER_FLOW;
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
void SLink<ElemType>::Set(int loc, const ElemType& e)
{
	if (loc < 1 || loc > length)
		throw RANGE_ERROR;
	int j = 1;
	for (int i = 1; i < loc; i++, j = node[j].next);
	node[j].data = e;
}

template<class ElemType>
int SLink<ElemType>::Find(const ElemType& e) const
{
	int j = 0, k = 0;//j游标，k计数
	for (; node[j].next != avail; j = node[j].next, k++)
	{
		if (node[j].data == e) return k;
	}
	if (node[j].data == e) return k;
	return NOT_FOUND;
}

template<class ElemType>
ElemType SLink<ElemType>::Search(const int loc) const
{
	if (loc < 1 || loc > length)
		throw RANGE_ERROR;
	int j = node[0].next;
	for (int i = 1; i < loc; i++)
	{
		j = node[j].next;
	}
	return node[j].data;
}

template<class ElemType>
int SLink<ElemType>::Length() const
{
	return length;
}

template<class ElemType> ElemType SLink<ElemType>::Delete(int loc)
{
	ElemType e;
	if (loc < 1 || loc > length)
		throw RANGE_ERROR;
	int j = 0;								//loc处的前一个结点
	for (int i = 0; i < loc - 1; i++)		//找到j
	{
		j = node[j].next;
	}
	int k = node[j].next;					//记录loc处的结点
	e = node[k].data;
	node[j].next = node[k].next;
	int p = avail;							//记录原avail
	avail = k;								//被删的结点自动成为新的avail
	node[k].next = p;					//avail间生成联系
	while (node[j].next != p)				//让j到有数据表的表尾
		j = node[j].next;
	node[j].next = avail;
	length--;
	return e;
}

template<class ElemType> void SLink<ElemType>::Reset()
{
	for (int i = 0; i < maxsize - 1; i++)
	{
		node[i].next = i + 1;		//第i个元素的next指向i+1 最后元素默认指-1
	}
	avail = 1;
	length = 0;
	maxsize = MAXSIZE;
}

template<class ElemType> void SLink<ElemType>::Reverse()
{
	if (length <= 1)
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
	if (length <= 1) return;
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
template<class ElemType>
void SLink<ElemType>::Enlarge(const int L)
{
	if (L <= maxsize) throw RANGE_ERROR;
	SNode<ElemType>* nNode = new SNode<ElemType>[L];
	for (int i = 0; i < maxsize; i++)
	{
		nNode[i] = node[i];
	}
	for (int i = maxsize; i < L; i++)
	{
		nNode[i].next = i + 1;
	}
	delete[] node;
	node = nNode;
	maxsize = L;
}

template<class ElemType>
SLink<ElemType>& SLink<ElemType>::operator=(const SLink<ElemType>& S)
{
	if (this == &S) return *this;
	delete[] node;
	length = S.length;
	maxsize = S.maxsize;
	node = new SNode<ElemType>[maxsize];
	for (int i = 0; i < maxsize; i++)
	{
		node[i] = S.node[i];
	}
	avail = S.avail;
	return *this;
}

template <class ElemType> ostream& operator <<(ostream& out, const SLink<ElemType>& link)
{
	link.Traverse(0, out);
	return out;
}

template <class ElemType> void SLink<ElemType>::Save(const char* filename) const		// 将链表所有结点的数据写入指定文件
{
	ofstream outfile;
	outfile.open(filename);
	if (outfile.fail())
		return;
	outfile << *this;
	outfile.close();
}

template<class ElemType> istream& operator >>(istream& in, SLink<ElemType>& link)
{
	link.Reset();
	int n;
	in >> n;
	for (int i = 1; i < n; i++)
	{
		in >> link.node[i].data;
	}
	link.avail = n;
	return in;
}
template <class ElemType> void SLink<ElemType>::Load(const char* filename)		// 从指定文件中读取数据，构造链表
{
	ifstream infile(filename);
	if (infile.fail())
		return;
	infile >> *this;
	infile.close();
}
