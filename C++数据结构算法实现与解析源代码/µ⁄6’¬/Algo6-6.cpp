//Algo6-6.cpp 验证DLTree类的成员函数
const int MAX_KEY_LEN=16;
#include "C.h"
const int N=18;
const char Nil='$';
enum style{Pre, In, Post};
#include "DLTree.h"
#include "Func6-5.cpp"
const int h=9;
void print(DLTNode<Ot>* c)
{
	cout<<c->symbol<<' ';
}
void main()
{
	int i, n;
	bool f;
	K key;
	DLTree<Ot> t;
	Record<Ot> r, *p;
	ifstream fin("F6-6.txt");
	fin>>n;
	for(i=0; i<n; i++)
	{
		InputFromFile(fin, r);
		f=t.InsertDSTable(r);
		if(!f)
			cout<<"record[]中已有关键字为"<<r.key.ch
			<<"的数据，或record[]中没有空位置无法插入。"<<endl;
	}
	t.TraverseDSTable(t.Root(), Out);
	cout<<endl;
	t.Print(Out);
	cout<<"请输入待查找的关键字符串：";
	InputKey(key);
	p=t.SearchDSTable(key);
	if(p!=NULL)
		Out(*p);
	for(i=0; i<3; i++)
	{
		cout<<endl<<"请输入待删除的关键字符串：";
		InputKey(key);
		if(t.DeleteDSTable(key, r))
		{
			cout<<"删除成功！其值为";
			Out(r);
		}
		else
			cout<<"删除失败！";
	}
	cout<<endl;
	j=0;
	t.TraverseDSTable(t.Root(), Out);
	cout<<endl;
	t.Print(Out);
}

