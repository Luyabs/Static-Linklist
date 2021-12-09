#pragma once

template <class ElemType>
struct SNode
{
	ElemType data;		// ������
	int next;			// ����next�򴴽�����е����ӹ�ϵ  ��next = -1 ������ͨ������next = NULL

	SNode();								// �ս��Ĺ��캯��
	SNode(ElemType DATA, int NEXT = -1);	// ��֪������Ԫ��ֵ��ָ�뽨���ṹ
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