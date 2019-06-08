//PBiTNode.h 三叉链表结点类型结构体
#ifndef _PBITNODE_H_
#define _PBITNODE_H_
template<typename T>struct PBiTNode
{
	T data;
	PBiTNode<T> *lchild, *rchild, *parent;
};
#endif

