//BiThrNode.h 线索二叉链表结点类型结构体
#ifndef _BITHRNODE_H_
#define _BITHRNODE_H_
enum PointerTag	{Link, Thread};
template<typename T>struct BiThrNode
{ 
	T data;
	BiThrNode<T> *lchild, *rchild;
	PointerTag LTag:2, RTag:2;
};
#endif

