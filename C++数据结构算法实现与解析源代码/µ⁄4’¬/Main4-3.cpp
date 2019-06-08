//Main4-3.cpp 验证线索二叉链表结构的二叉树BiThrTree<T>类的成员函数
#include "C.h"
#include "BiThrTree.h"
#define BiTNode BiThrNode
typedef char T;
T Nil='#';
#include "Func4-1.cpp"
void main()
{
	BiThrTree<T> t;
	t.CreateBiThrTreeFromFile("F4-1.txt");
	t.PreOrderThreading();
	cout<<"先序遍历线索二叉树t：";
	t.PreOrderTraverse(Visit);
	t.InOrderThreading();
	cout<<endl<<"中序遍历线索二叉树t：";
	t.InOrderTraverse(Visit);
	t.PostOrderThreading();
	cout<<endl;
}

