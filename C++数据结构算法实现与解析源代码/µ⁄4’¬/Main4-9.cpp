//Main4-9.cpp 用CSTree<T>类构造森林
#include "C.h"
#include "CSTree.h"
#define BiTNode CSNode
typedef char T;
#include "Func4-1.cpp"
void main()
{
	CSTree<T>t;
	t.CreateTreeFromFile("F4-9.txt");
	cout<<"由文件F4-9.txt创建森林t后，森林的深度（所有树中深度最大的树的深度）为";
	cout<<t.TreeDepth()<<endl<<"层序遍历森林t：";
	t.LevelOrderTraverse(Visit);
	cout<<endl<<"先根遍历森林t：";
	t.PreOrderTraverse(Visit);
	cout<<endl<<"后根遍历森林t：";
	t.PostOrderTraverse(Visit);
	cout<<endl;
}

