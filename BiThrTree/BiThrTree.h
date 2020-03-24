#pragma once

#include "../Common/TypeUnit.h"
#include "../Common/ErrorCode.h"
#include <stdlib.h>
#include <iostream>

using std::cin;
using std::cout;

/*线索二叉树*/

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
	PNodeType _thread;	// 线索化时，增加的线索头节点指针。
	PNodeType _root;	// 无线索节点的二叉树头节点指针。
};

template <typename T>
Status BiThrTree<T>::CreateBiThrTree()
{
	return BiThrTree<T>::CreateBiThrTree(this->_root);
}

template <typename T>
Status BiThrTree<T>::CreateBiThrTree(PNodeType& node)
{
	//次二叉树的创建顺序为 ：先创建根节点，然后左子树，最后右子树；

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
	// 销毁线索头节点。
	if (this->_thread) {
		delete this->_thread;
		this->_thread = NULL;
	}

	// 销毁线索二叉树
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
 * 中序遍历线索二叉树。
 * 思路：对于任意节点
 * 1、先循环找到第一个没有左子树的节点，访问此节点。
 * 2、再循环判断右子树是否为线索，若是则指向线索，并访问此节点。
 * 3、此时右子树不为线索，应该指向右子树，进入下一轮循环（即第1步）。
 */
template <typename T>
Status BiThrTree<T>::InOrderTraverse_Thr(Status(*visit)(T e))
{
	// 判断是否已经线索化。
	if (!this->_thread) {
		return FALSE;
	}

	PNodeType p = this->_thread->lchild; // 指针指向中序遍历的第一个结点

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
}// 复杂度也为O(n)，但是没有递归，不需要栈

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
 * 中序线索化二叉树。
 * 思路：对于任一节点，为空直接返回，不为空按如下处理：
 * 1、判断左子树是否为空，为空则标为线索，指向前驱；不为空则标为Link，线索化左子树，此时传入的前驱不变，后继为本节点。
 * 2、判断右子树是否为空，为空则标为线索，指向后继；不为空则标为Link，线索化右子树，此时传入的前驱为本节点，后继不变。
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
	//_root为原二叉树,_thread指向新增的线索化头节点

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
		pre->rchild = _thread;//处理最后一个结点
		_thread->rchild = pre;
	}
}//中序线索化

template <typename T>
void BiThrTree<T>::InThreading2(PNodeType p, PNodeType& pre) {
	//递归求解。空时无操作。
	//树非空则先递归地向左子树中添加线索信息(线索化作子树),后处理与根结点p相关的线索信息，最后递归的线索化右子树.
	//注意处理左右子树时pre的取值
	if (p) {
		InThreading2(p->lchild, pre); //线索化左子树   
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
		InThreading2(p->rchild, pre);//线索化右子树
	}
}
