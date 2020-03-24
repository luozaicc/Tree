#ifndef __STACK_H__
#define __STACK_H__

#include "TypeUnit.h"
#include "ErrorCode.h"
#include "Stack.h"
#include <stdlib.h>

/**
 * 栈模板类.
 */

template<typename T>
void CopyType(T& a, T b) {
	a = b;
}

template<typename T>
class Stack
{
public:
	Stack();
	~Stack();

	Status InitStack(Stack& S);
	Status DestroyStack(Stack& S);
	void ClearStack(Stack& S);
	Status EmptyStack(Stack S);
	Status Push(Stack& S, T e);
	Status Pop(Stack& S, T& e);
	Status GetTop(Stack S, T& e);
	Status SetTop(Stack& S, T e);

public:
	T* base;
	T* top;
	int stacksize;
};


template<typename T>
Stack<T>::Stack()
{
	base = NULL;
	top = NULL;
	stacksize = 0;
}

template<typename T>
Stack<T>::~Stack()
{
}

template<typename T>
Status Stack<T>::InitStack(Stack& S)
{
	//建立一个空栈；
	S.base = (T*)malloc(sizeof(T));

	if (!S.base)
		exit(EC_OVERFLOW);

	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

template<typename T>
Status Stack<T>::DestroyStack(Stack& S)
{
	free(S.base);
	S.top = NULL;
	S.base = NULL;
	S.stacksize = 0;
	return OK;
}

template<typename T>
void Stack<T>::ClearStack(Stack& S)
{
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

template<typename T>
Status Stack<T>::EmptyStack(Stack S)
{
	if (S.top - S.base)
		return FALSE;

	return OK;
}

template<typename T>
Status Stack<T>::Push(Stack<T>& S, T e)
{
	if (!S.top) {
		return FALSE;
	}
	if (S.top - S.base == S.stacksize) {
		Stack SS;
		SS.top = (T*)realloc(S.base, sizeof(S.stacksize + STACKINCREMENT));
		if (!SS.base)
			exit(EC_OVERFLOW);

		free(S.base);
		S.base = SS.base;
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	CopyType(*S.top, e);
	S.top++; return OK;
}

template<typename T>
Status Stack<T>::Pop(Stack<T>& S, T& e)
{
	if (S.top == S.base)
		return FALSE;

	CopyType(e, *(S.top - 1));
	--S.top;
	return OK;
}

template<typename T>
Status Stack<T>::GetTop(Stack S, T& e)
{
	if (S.top == S.base)
		return FALSE;

	CopyType(e, *(S.top - 1));
	return OK;
}

template<typename T>
Status Stack<T>::SetTop(Stack& S, T e)
{
	if (EmptyStack(S))
		return FALSE;

	CopyType(*(S.top - 1), e);
	return OK;
}

#endif //__STACK_H__