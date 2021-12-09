#pragma once

template <class ElemType>
struct SNode
{
	ElemType data;		// 数据域
	int next;			// 根据next域创建结点中的连接关系  将next = -1 比作普通链表中next = NULL

	SNode();								// 空结点的构造函数
	SNode(ElemType DATA, int NEXT = -1);	// 已知数数据元素值和指针建立结构
};


template <class ElemType> SNode<ElemType>::SNode()
{
	next = -1;
}

template <class ElemType> SNode<ElemType>::SNode(ElemType DATA, int NEXT)
{
	data = DATA;
	next = -1;
}