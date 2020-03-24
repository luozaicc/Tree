#ifndef __BITREE_H__
#define __BITREE_H__

#include "TypeUnit.h"
#include "ErrorCode.h"
#include "Stack.h"
#include "iostream"

using std::cin;
using std::cout;

/**
 * 二叉树链表表示法
 */
template <typename T>
struct BiTNode {
	T data;
	struct BiTNode<T>* lchild;
	struct BiTNode<T>* rchild;
};

template <typename T>
class BiTree {
public :
	typedef BiTNode<T> NodeType;
	typedef BiTNode<T>* PNodeType;

	BiTree();
	~BiTree();

	Status InitBiTree();
	Status CreateBiTree();
	static Status CreateBiTree(PNodeType& node);
	Status DestroyBiTree();
	static Status DestroyBiTree(PNodeType& node);
	Status BiTreeEmpty();
	static Status BiTreeEmpty(PNodeType T);
	int BiTreeDepth();
	static int BiTreeDepth(PNodeType T);
	Status InsertChild(PNodeType p, int LR, PNodeType c);
	Status DeleteChild(PNodeType p, int LR);
	//Status Assign(BiTree T, BiTree cur_e, TElemType value);
	Status InOrderTraverse_NonRecur_1(Status(*visit)(T));
	Status InOrderTraverse_NonRecur_2(Status(*visit)(T));
	//Status PreOrderTraverse(PNodeType T, Status(*Visit)(T e);
	//Status InOrderTraverse(BiTree T, Status(*Visit)(T e));
	//Status PostOrderTraverse(BiTree T, Status(*Visit)(T e));
	//Status LevelOrderTraverse(BiTree T, Status(*Visit)(T e));
	//Status CopyBiTree(BiTree T, BiTree& X);
	//Status LocateNode(BiTree T, TElemType x, BiTree& p);
	//Status LocateParent(BiTree T, TElemType x, BiTree& parent_p, int& LR);
	//Status DeleteChild(BiTree& T, TElemType x);
	//Status ChangeLR(BiTree T);
	//int LeafCount(BiTree T);
	//int BiTNodeCount(BiTree T);
	//void PrintBiTree(BiTree T);
private:
	PNodeType _root;
};


template <typename T>
BiTree<T>::BiTree()
{
	_root = NULL;
}

template <typename T>
BiTree<T>::~BiTree()
{
	DestroyBiTree();
}

template <typename T>
Status BiTree<T>::InitBiTree()
{
	if (_root) {
		return OK;
	}

	_root = (PNodeType)malloc(sizeof(NodeType));
	if (!_root) exit(EC_OVERFLOW);
	_root->lchild = NULL;
	_root->rchild = NULL;
	return OK;
}


template <typename T>
Status BiTree<T>::CreateBiTree()
{
	return BiTree<T>::CreateBiTree(this->_root);
}

template <typename T>
Status BiTree<T>::CreateBiTree(PNodeType &node)
{
	//次二叉树的创建顺序为 ：先创建根节点，然后左子树，最后右子树；

	T e;
	cin >> e;
	if (e != 0)
	{
		node = (PNodeType)malloc(sizeof(NodeType));
		if (!node)exit(OVERFLOW);
		node->data = e;
		CreateBiTree(node->lchild);
		CreateBiTree(node->rchild);
		return OK;
	}
	else node = NULL;

	return OK;
}


template <typename T>
Status BiTree<T>::DestroyBiTree()
{
	return BiTree<T>::DestroyBiTree(this->_root);
}

template <typename T>
Status BiTree<T>::DestroyBiTree(PNodeType& node)
{
	if (node) {
		DestroyBiTree(node->lchild);
		DestroyBiTree(node->rchild);
		free(node);
		node = NULL;
		return OK;
	}
	else return OK;
}

/*
void DesBiT_FeiDiGui(BiTree &T)
{
	//非递归的二叉树删除，有一点问题 。。。
	Stack S,D;InitStack(S);InitStack(D);BiTNode*b=T;
	while(b||!EmptyStack(S))
	{
		if(b){Push(S,b);b=b->lchild;}
		else{
			GetTop(S,b);b=b->rchild;
			if(b)continue;
			else {Pop(S,b);free(b);b->rchild=NULL;b->lchild=NULL;
			if(!Pop(S,b))return OK;b->rchild=NULL;b->lchild=NULL;
			}
		}
	}
}
*/

template <typename T>
Status BiTree<T>::BiTreeEmpty()
{
	return BiTree<T>::BiTreeEmpty(this->_root);
}

template <typename T>
Status BiTree<T>::BiTreeEmpty(PNodeType node)
{
	//二叉树已经存在，判断树空；操作结果：空返回TRUE；不空返回FALSE；
	if (node)
		return FALSE;

	return TRUE;
}

template <typename T>
Status BiTree<T>::BiTreeDepth()
{
	return BiTree<T>::BiTreeDepth(this->_root);
}

template <typename T>
int BiTree<T>::BiTreeDepth(PNodeType node)
{
	//二叉树已经存在。操作结果：返回二叉树的深度 ；
	int r;
	if (node)
	{
		int a = 0, b = 0;
		a = BiTreeDepth(node->lchild);
		b = BiTreeDepth(node->rchild);
		r = a > b ? a : b;
		++r;
	}
	else r = 0;

	return r;
}

template <typename T>
Status BiTree<T>::InsertChild(PNodeType p, int LR, PNodeType c)
{
	//LR为0或1,插入右子树为空的二叉树c为T中p所指结点的左或右子树
	//0为 lchild;1为rchild
	PNodeType a;
	if (LR) {
		a = p->rchild;
		p->rchild = c;
		c->rchild = a;
	}
	else {
		a = p->lchild; p->lchild = c; c->rchild = a;
	}return OK;
}

template <typename T>
Status BiTree<T>::DeleteChild(PNodeType node, int LR)
{
	// 删除结点p的左或右子树,注意p为指针类型。
	BiTNode* a, * b;
	if (LR) {
		b = node->rchild;
		node->rchild = NULL;
	}
	else {
		b = node->lchild;
		node->lchild = NULL;
	}
	DestroyBiTree(b);
	return OK;
}

//template <typename T>
//Status BiTree<T>::Assign(BiTree T, BiTree cur_e, TElemType value)
//{
//	//给cur_e结点赋值
//	cur_e->data = value; return OK;
//}

/*
Status Root(BiTree T)
Status Value(BiTree T, cur_e)
Status Parent(BiTree T, cur_e)
Status LeftChild(BiTree T,cur_e)返回T中cur_e结点的左孩子,作为左子树的根可代表左子树
Status RightChild(BiTree T,cur_e)求T中cur_e结点的右孩子,作为右子树的根可代表右子树
Status RightSibling(BiTree T, cur_e) 求cur_e结点的右兄弟
{

}*/

template <typename T>
Status BiTree<T>::InOrderTraverse_NonRecur_1(Status(*visit)(T))
{
	//中序非递归遍历。
	//思路 ：只要树根节点不空，就将根节点入栈，指向左孩子，左子树作为根节点。
	//否则将上一个根节点弹出，访问根节点的data；然后 指向右孩子，就将右孩子作为根节点，进行下一次循环；
	//停止的条件是：当前节点空，并且栈为空；
	Stack<PNodeType> S;
	S.InitStack(S);
	PNodeType p = this->_root;
	while (p || !S.EmptyStack(S)) {
		while (p) {
			S.Push(S, p);
			p = p->lchild;
		}
		S.Pop(S, p);
		(*visit)(p->data);
		p = p->rchild;
	}

	return OK;
}

template <typename T>
Status BiTree<T>::InOrderTraverse_NonRecur_2(Status(*visit)(T))
{
	//中序非递归遍历。
	//当根节点不空时，将他的左孩子入栈，进行下一次循环。
	//否则，当前空节点出栈， 访问栈顶元素，将右孩子入栈，
	//结束条件：栈为空。
	Stack<PNodeType> S;
	S.InitStack(S);
	PNodeType p = this->_root;
	if (!p) {
		printf("\n空树。\n");
		return ERROR;
	}
	else {
		S.Push(S, p);
		while (!S.EmptyStack(S)) {
			while (S.GetTop(S, p) && p) {
				S.Push(S, p->lchild);
			}

			S.Pop(S, p);
			
			if (!S.EmptyStack(S)) {
				S.Pop(S, p);
				(*visit)(p->data);
				S.Push(S, p->rchild);
			}
		}
	}
	return OK;
}

/*
template <typename T>
Status BiTree<T>::PreOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	//先序遍历
	if (T)
	{
		if ((*Visit)(T->data))
			if (PreOrderTraverse(T->lchild, *Visit))
				if (PreOrderTraverse(T->rchild, *Visit))return OK;
				else return ERROR;
	}
	return OK;
}

template <typename T>
Status BiTree<T>::InOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	//中序遍历
	if (T)
	{
		if (InOrderTraverse(T->lchild, *Visit))
			if ((*Visit)(T->data));
		if (InOrderTraverse(T->rchild, *Visit))return OK;
		else return ERROR;
	}
	else return OK;
}

template <typename T>
Status BiTree<T>::PostOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	//后序遍历
	if (T)
	{
		if (PostOrderTraverse(T->lchild, *Visit))
			if (PostOrderTraverse(T->rchild, *Visit))
				if ((*Visit)(T->data))return OK;
				else return ERROR;
	}
	else return OK;
}

template <typename T>
Status BiTree<T>::LevelOrderTraverse(BiTree T, Status(*Visit)(TElemType e))
{
	//层次遍历
	return OK;
}
*/
/*
Status Traverse(BiTree T,Status(*f)(BiTree,BiTree),BiTree&e)
{
	//遍历二叉树 ，找到第一个满足条件f的节点，用e吧节点地址带回；
	Stack S;InitStack(S);BiTNode*p=T;
	while(p||!EmptyStack(S))
	{
		if(p){
			Push(S,p);p=p->lchild;
		}
		else {
			Pop(S,p);if((*f)(p,))
		}
	}
}*/

/*
template <typename T>
Status BiTree<T>::CopyBiTree(BiTree T, BiTree& X)
{
	//复制树T得到树X，T保持不变
	if (T) {
		X = (BiTree)malloc(sizeof(BiTNode));
		if (!X)exit(OVERFLOW);
		X->data = T->data;
		CopyBiTree(T->lchild, X->lchild); CopyBiTree(T->rchild, X->rchild);
	}
	else X = NULL;
	return OK;
}

template <typename T>
Status BiTree<T>::LocateNode(BiTree T, TElemType x, BiTree& p)
{
	//在树T中查找(按先序)第一个结点值等于x的结点，若找到则函数返回ＴＲＵＥ,
	//p带回该结点的地址;若找不到则函数返回ＦＡＬＳＥ　，p赋值为NULL
	if (T)
	{
		if (T->data == x) { p = T; return OK; }
		else {
			if (LocateNode(T->lchild, x, p))return OK;
			else if (LocateNode(T->rchild, x, p))return OK;
			else { p = NULL; return ERROR; }
		}
	}
	else p = NULL; return ERROR;
}

template <typename T>
Status BiTree<T>::LocateParent(BiTree T, TElemType x, BiTree& parent_p, int& LR)
{
	//已知树T中存在某结点值等于x，定位到该结点的双亲结点,若双亲存在（说明x结点非根结点）则parent_p带回双亲位置，
	//flag为代表是双亲的左孩子，为代表是双亲的右孩子，同时函数返回ＴＲＵＥ；否则函数返回FALSE

}

template <typename T>
Status BiTree<T>::DeleteChild(BiTree& T, TElemType x)
{
	//删除树T中以x为根结点的子树,若存在x结点则删除成功后返回OK，若不存在x结点返回ERROR;
	Stack S, D; InitStack(S); InitStack(D); SElemType e; BiTNode* p = T, * q;
	while (p || !EmptyStack(S))
	{
		if (p->data == x)
			while (p || !EmptyStack(D))
			{
				if (p && p->lchild && p->rchild) {
					Push(D, p); p = p->lchild;
				}
			}
	}
}

template <typename T>
Status BiTree<T>::ChangeLR(BiTree T)
{
	if (T)
	{
		BiTNode* c = T->rchild; T->rchild = T->lchild; T->lchild = c;
		ChangeLR(T->lchild); ChangeLR(T->rchild);
	}
	return OK;
}

template <typename T>
int BiTree<T>::LeafCount(BiTree T)
{
	//计算二叉树T 的叶子树；并返回
	int r;
	if (T) r = 0;
	else if (!T && !T->rchild && !T->lchild)r = 1;
	else r = LeafCount(T->lchild) + LeafCount(T->rchild);
	return r;
}

template <typename T>
int BiTree<T>::BiTNodeCount(BiTree T)
{
	//返回二叉树的节点数
	int r;
	if (T) {
		r = BiTNodeCount(T->lchild) + BiTNodeCount(T->rchild) + 1;
	}
	else r = 0;
	return r;
}

template <typename T>
void BiTree<T>::PrintBiTree(BiTree T)
{
	//凹式输出一个二叉树；采用全局变量的方法count为全局变量；初值为0；
	BiTNode* r = T;
	if (r)
	{
		for (int i = 0; i < count; i++)printf("  ");//打印空格数为count次。
		PrintTElem(r->data); printf("\n"); count++;
		PrintBiTree(r->lchild);
		PrintBiTree(r->rchild); count--;
	}
	//	else{for(int i=0;i<count;i++)printf("  "); printf("%4d\n",0); }
}
*/


#endif //__BITREE_H__