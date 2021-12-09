#pragma once
#include "SNode.h"
#include <iostream>
using namespace std;

const int MAXSIZE = 100;		//ÿ�����������Ĵ�С
const int RANGE_ERROR = 1001;	//Խ���׳�1001

template <class ElemType> class SLink		//��ǰ ���� ��ѭ��  ����֮���ٸ�
{
protected:
	SNode<ElemType> *node;		//��nodeָ��������׽�� �Դ���Ϊ��̬�����׽�� node[0]����ͨ������׽������
	int avail;					//��̬������һ����λ���±� ����ȥnode[0]������û��data�Ľ�� ����Ϊ�ձ� �ձ���׽��Ϊavail avail����ɾ����Ҫ����
	int length;					//��ǰ��ӵ�еĽ����(������head)

public:
	SLink();					//����ռ� ��next�ѽ������һ�� ����ձ� 
	virtual ~SLink();
	void Traverse(bool write = true) const;		//����(���/�����)
	void Insert(const ElemType& e);				//β�巨 //������ɺ� avail�Զ�����ƣ�ɾ����ɺ� avail�䵽��ɾ����λ�� 
	void Insert(int loc, const ElemType& e);		//���룬ʹe��Ϊ�����loc��Ԫ��(����head)

};


template<class ElemType> SLink<ElemType>::SLink() : length(0),avail(1)
{
	node = new SNode<ElemType>[MAXSIZE];
	for (int i = 0; i < MAXSIZE - 1; i++) 
	{
		node[i].next = i + 1;		//��i��Ԫ�ص�nextָ��i+1 ���Ԫ��Ĭ��ָ-1
	}
}

template<class ElemType> SLink<ElemType>::~SLink()
{
	delete[] node;
	length = 0;
}

template <class ElemType> void SLink<ElemType>::Traverse(bool write) const	//write == 1 ���һ������, write == 0 ���ƶ�����β
{
	int p = node[0].next;
	if (write)
	{
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
			p = node[p].next;
		}
	}
}

template<class ElemType> void SLink<ElemType>::Insert(const ElemType& e)
{
	node[avail].data = e;			
	avail = node[avail].next;		//avail�ƶ����ձ����һ��λ��
	length++;
}

template<class ElemType> void SLink<ElemType>::Insert(int loc, const ElemType& e)
{
	if (loc < 1 || loc > length + 1)
		throw RANGE_ERROR;
	node[avail].data = e;		
	int j = node[0].next;							//loc����ǰһ�����
	int p = avail;					//��¼����������ݵĽ��
	avail = node[avail].next;		//avail�ƶ����ձ����һ��λ��
	for (int i = 0; i < loc - 1; i++)		//�ҵ�j
	{
		j = node[j].next;
	}
	node[p].next = node[j].next;		//��������
	node[j].next = p;				
	length++;
}






























/*
template <class ElemType>
class SLink		//��ǰ��ͷ��� ���� ��ѭ��  ����֮���ٸ�
{
protected:
	SNode<ElemType> head;		//��ͷ���	p = link[p.next]�൱��p = p->next 
	int avail;			//��̬�����λ���±�
	int length;			//��ǰ��ӵ�еĽ����(������head)
	int max_length;		//�����ӵ�еĽ����(������head)(�ɳ�ʼ������Ķ�̬�ڴ����)

public:
	//������������: �п�,���,���س���/��󳤶�,���� ��

	//�������ܺ�������,ɾ,��,��,����,�ϲ�,���� ��
	void SLink<ElemType>::Insert(const ElemType& e);		//β��

	//����ΪMax_length����(���·��������ڴ�ռ� �� copy �� delete)  ���� ������������ͬ�ľ�̬��������ϵ������

	//����� + �������������

	//�Ĵ���
	SLink();
	SLink(ElemType arr[], int n);
	virtual ~SLink();
	SLink(const SLink<ElemType>& link);
	SLink<ElemType>& operator = (const SLink<ElemType>& link);

};

template <class ElemType> SLink<ElemType>::SLink()
{
	head = new SNode<ElemType>;		//�����ͷ
	avail = -1;					//����û�п�λ
	length = 0;						
}

template <class ElemType> void SLink<ElemType>::Insert(const ElemType& e)
{
	SNode<ElemType> p, q;
	q = new Node<ElemType>(e, -1);    // �����½��q
	for (p = head; p.next != -1; p = p->next);	// pָ���β���	
	p->next = q;                        // �ڵ�����ı�βλ�ò����½�� 
	length++;							// ����ɹ��󣬵������ȼ�1 

}




template <class ElemType> SLink<ElemType>::SLink(ElemType arr[], int n)
{
	max_length = 2 * n + 1;
	ElemType link = new SNode<ElemType>(max_length);		//�����������ѿռ��sll����

	link[0] = head;								//���� 0->n ˳���趨nextΪ��Ȼ���� ����벻ͬ
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
