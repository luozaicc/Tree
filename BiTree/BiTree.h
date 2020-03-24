#ifndef __BITREE_H__
#define __BITREE_H__

#include "TypeUnit.h"
#include "ErrorCode.h"
#include "Stack.h"
#include "iostream"

using std::cin;
using std::cout;

/**
 * �����������ʾ��
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
	//�ζ������Ĵ���˳��Ϊ ���ȴ������ڵ㣬Ȼ���������������������

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
	//�ǵݹ�Ķ�����ɾ������һ������ ������
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
	//�������Ѿ����ڣ��ж����գ�����������շ���TRUE�����շ���FALSE��
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
	//�������Ѿ����ڡ�������������ض���������� ��
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
	//LRΪ0��1,����������Ϊ�յĶ�����cΪT��p��ָ�������������
	//0Ϊ lchild;1Ϊrchild
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
	// ɾ�����p�����������,ע��pΪָ�����͡�
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
//	//��cur_e��㸳ֵ
//	cur_e->data = value; return OK;
//}

/*
Status Root(BiTree T)
Status Value(BiTree T, cur_e)
Status Parent(BiTree T, cur_e)
Status LeftChild(BiTree T,cur_e)����T��cur_e��������,��Ϊ�������ĸ��ɴ���������
Status RightChild(BiTree T,cur_e)��T��cur_e�����Һ���,��Ϊ�������ĸ��ɴ���������
Status RightSibling(BiTree T, cur_e) ��cur_e�������ֵ�
{

}*/

template <typename T>
Status BiTree<T>::InOrderTraverse_NonRecur_1(Status(*visit)(T))
{
	//����ǵݹ������
	//˼· ��ֻҪ�����ڵ㲻�գ��ͽ����ڵ���ջ��ָ�����ӣ���������Ϊ���ڵ㡣
	//������һ�����ڵ㵯�������ʸ��ڵ��data��Ȼ�� ָ���Һ��ӣ��ͽ��Һ�����Ϊ���ڵ㣬������һ��ѭ����
	//ֹͣ�������ǣ���ǰ�ڵ�գ�����ջΪ�գ�
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
	//����ǵݹ������
	//�����ڵ㲻��ʱ��������������ջ��������һ��ѭ����
	//���򣬵�ǰ�սڵ��ջ�� ����ջ��Ԫ�أ����Һ�����ջ��
	//����������ջΪ�ա�
	Stack<PNodeType> S;
	S.InitStack(S);
	PNodeType p = this->_root;
	if (!p) {
		printf("\n������\n");
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
	//�������
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
	//�������
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
	//�������
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
	//��α���
	return OK;
}
*/
/*
Status Traverse(BiTree T,Status(*f)(BiTree,BiTree),BiTree&e)
{
	//���������� ���ҵ���һ����������f�Ľڵ㣬��e�ɽڵ��ַ���أ�
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
	//������T�õ���X��T���ֲ���
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
	//����T�в���(������)��һ�����ֵ����x�Ľ�㣬���ҵ��������أԣңգ�,
	//p���ظý��ĵ�ַ;���Ҳ����������أƣ��̣ӣš���p��ֵΪNULL
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
	//��֪��T�д���ĳ���ֵ����x����λ���ý���˫�׽��,��˫�״��ڣ�˵��x���Ǹ���㣩��parent_p����˫��λ�ã�
	//flagΪ������˫�׵����ӣ�Ϊ������˫�׵��Һ��ӣ�ͬʱ�������أԣңգţ�����������FALSE

}

template <typename T>
Status BiTree<T>::DeleteChild(BiTree& T, TElemType x)
{
	//ɾ����T����xΪ����������,������x�����ɾ���ɹ��󷵻�OK����������x��㷵��ERROR;
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
	//���������T ��Ҷ������������
	int r;
	if (T) r = 0;
	else if (!T && !T->rchild && !T->lchild)r = 1;
	else r = LeafCount(T->lchild) + LeafCount(T->rchild);
	return r;
}

template <typename T>
int BiTree<T>::BiTNodeCount(BiTree T)
{
	//���ض������Ľڵ���
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
	//��ʽ���һ��������������ȫ�ֱ����ķ���countΪȫ�ֱ�������ֵΪ0��
	BiTNode* r = T;
	if (r)
	{
		for (int i = 0; i < count; i++)printf("  ");//��ӡ�ո���Ϊcount�Ρ�
		PrintTElem(r->data); printf("\n"); count++;
		PrintBiTree(r->lchild);
		PrintBiTree(r->rchild); count--;
	}
	//	else{for(int i=0;i<count;i++)printf("  "); printf("%4d\n",0); }
}
*/


#endif //__BITREE_H__