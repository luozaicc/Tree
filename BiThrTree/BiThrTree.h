#pragma once

#include "../Common/TypeUnit.h"
#include "../Common/ErrorCode.h"
#include <stdlib.h>
#include <iostream>

using std::cin;
using std::cout;

/*����������*/

typedef enum { Link, Thread }PointerTag;

template <typename T>
struct BiThrTNode {
	T data;
	PointerTag lTag;
	PointerTag rTag;
	struct BiThrTNode* lchild;
	struct BiThrTNode* rchild;
};


template <typename T>
class BiThrTree {
public:
	typedef BiThrTNode<T> NodeType;
	typedef BiThrTNode<T>* PNodeType;

	BiThrTree() {
		_thread = NULL;
		_root = NULL;
	}

	Status CreateBiThrTree();
	static Status CreateBiThrTree(PNodeType& node);
	Status DestroyBiThrTree();
	static Status DestroyBiThrTree(PNodeType& node);
	Status InOrderTraverse_Thr(Status(*visit)(T e));
	void InOrderThreading();
	void InOrderThreading2();

private:
	void InThreading(PNodeType node, PNodeType preNode, PNodeType postNode);
	void InThreading2(PNodeType p, PNodeType& pre);
private:
	PNodeType _thread;	// ������ʱ�����ӵ�����ͷ�ڵ�ָ�롣
	PNodeType _root;	// �������ڵ�Ķ�����ͷ�ڵ�ָ�롣
};

template <typename T>
Status BiThrTree<T>::CreateBiThrTree()
{
	return BiThrTree<T>::CreateBiThrTree(this->_root);
}

template <typename T>
Status BiThrTree<T>::CreateBiThrTree(PNodeType& node)
{
	//�ζ������Ĵ���˳��Ϊ ���ȴ������ڵ㣬Ȼ���������������������

	T e;
	cin >> e;
	if (e != 0)
	{
		node = new NodeType;
		node->data = e;
		CreateBiThrTree(node->lchild);
		CreateBiThrTree(node->rchild);
		return OK;
	}
	else node = NULL;

	return OK;
}

template <typename T>
Status BiThrTree<T>::DestroyBiThrTree()
{
	// ��������ͷ�ڵ㡣
	if (this->_thread) {
		delete this->_thread;
		this->_thread = NULL;
	}

	// ��������������
	return BiThrTree<T>::DestroyBiThrTree(this->_root);
}

template <typename T>
Status BiThrTree<T>::DestroyBiThrTree(PNodeType& t)
{
	if (t) {
		if (Link == t->lTag) {
			DestroyBiThrTree(t->lchild);
		}

		if (Link == t->rTag) {
			DestroyBiThrTree(t->rchild);
		}
		
		delete t;
		t = NULL;
		return OK;
	}
	else return OK;
}

/**
 * �������������������
 * ˼·����������ڵ�
 * 1����ѭ���ҵ���һ��û���������Ľڵ㣬���ʴ˽ڵ㡣
 * 2����ѭ���ж��������Ƿ�Ϊ������������ָ�������������ʴ˽ڵ㡣
 * 3����ʱ��������Ϊ������Ӧ��ָ����������������һ��ѭ��������1������
 */
template <typename T>
Status BiThrTree<T>::InOrderTraverse_Thr(Status(*visit)(T e))
{
	// �ж��Ƿ��Ѿ���������
	if (!this->_thread) {
		return FALSE;
	}

	PNodeType p = this->_thread->lchild; // ָ��ָ����������ĵ�һ�����

	while (p != this->_thread) {
		while (Link == p->lTag) {
			p = p->lchild;
		}
		(*visit)(p->data);

		if (Link == p->rTag) {
			p = p->rchild;
			continue;
		}

		while (Thread == p->rTag && p->rchild != this->_thread) {
			p = p->rchild;
			(*visit)(p->data);
		}
		p = p->rchild;
	}

	return OK;
}// ���Ӷ�ҲΪO(n)������û�еݹ飬����Ҫջ

template <typename T>
void BiThrTree<T>::InOrderThreading()
{
	if (!_thread) {
		_thread = new NodeType;
	}
	_thread->lTag = Link;
	_thread->lchild = _thread;
	_thread->rTag = Thread;
	_thread->rchild = _thread;

	if (_root) {
		_thread->lchild = _root;
		InThreading(_root, _thread, _thread);
	}
}

/**
 * ������������������
 * ˼·��������һ�ڵ㣬Ϊ��ֱ�ӷ��أ���Ϊ�հ����´���
 * 1���ж��������Ƿ�Ϊ�գ�Ϊ�����Ϊ������ָ��ǰ������Ϊ�����ΪLink������������������ʱ�����ǰ�����䣬���Ϊ���ڵ㡣
 * 2���ж��������Ƿ�Ϊ�գ�Ϊ�����Ϊ������ָ���̣���Ϊ�����ΪLink������������������ʱ�����ǰ��Ϊ���ڵ㣬��̲��䡣
 */
template <typename T>
void BiThrTree<T>::InThreading(PNodeType node, PNodeType preNode, PNodeType postNode)
{
	if (node) {
		if (NULL == node->lchild) {
			node->lTag = Thread;
			node->lchild = preNode;
		}
		else {
			node->lTag = Link;
			InThreading(node->lchild, preNode, node);
		}
		if (NULL == node->rchild) {
			node->rTag = Thread;
			node->rchild = postNode;
		}
		else {
			node->rTag = Link;
			InThreading(node->rchild, node, postNode);
		}
	}
}

template <typename T>
void BiThrTree<T>::InOrderThreading2() {
	//_rootΪԭ������,_threadָ��������������ͷ�ڵ�

	if (!_thread) {
		_thread = new NodeType;
	}
	_thread->lTag = Link;
	_thread->lchild = _thread;
	_thread->rTag = Thread;
	_thread->rchild = _thread;

	if (_root) {
		_thread->lchild = _root;
		PNodeType pre = _thread;
		InThreading2(_root, pre);
		pre->rTag = Thread;
		pre->rchild = _thread;//�������һ�����
		_thread->rchild = pre;
	}
}//����������

template <typename T>
void BiThrTree<T>::InThreading2(PNodeType p, PNodeType& pre) {
	//�ݹ���⡣��ʱ�޲�����
	//���ǿ����ȵݹ���������������������Ϣ(������������),����������p��ص�������Ϣ�����ݹ��������������.
	//ע�⴦����������ʱpre��ȡֵ
	if (p) {
		InThreading2(p->lchild, pre); //������������   
		if (p->lchild == NULL) {
			p->lTag = Thread;
			p->lchild = pre;
		}
		else p->lTag = Link;
		if (pre->rchild == NULL) {
			pre->rTag = Thread;
			pre->rchild = p;
		}
		else pre->rTag = Link;

		pre = p;
		InThreading2(p->rchild, pre);//������������
	}
}
